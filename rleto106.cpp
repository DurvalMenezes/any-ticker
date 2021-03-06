#include "stdafx.h"
#include "rleto106.h"
#include "coordinate.h"
#include "life_object.h"

using namespace std;

extern int debugFlag;
extern string outputFileName;

bool starts_with(const string& s, const string& prefix) {
   auto size = prefix.size();
   if (s.size() < size) return false;
   return equal(begin(prefix), end(prefix), begin(s));
}

int rleto106(int argc, char *argv[]){
	outputFileName = "newfile.life";

	/* open the input file */
	FILE *rleFile;
	if( argc > 1){
		rleFile = fopen( argv[1], "r");
		if( rleFile == NULL){
			printf("Can't open %s. Try again.\n", argv[1]);
			return 1;
		}
	}else{
		cout << "Please input file rle file name." << endl;
		exit(1);
	}

	/* skipping lines starting with '#' */
	char line[100000];
	line[0] = '#';
	const string PREFIX = "#CXRLE";
	Coordinate centre(0, 0);
	while( line[0] == '#'){
		fgets( line, sizeof(line), rleFile);
		if(starts_with(string(line), PREFIX)) {
			int x, y;
			sscanf(line, "#CXRLE Pos=%d,%d", &x, &y);
			centre = Coordinate(x, y);
		}
	}

	char string[100000];
	fgets( string, sizeof(string), rleFile);
	string[strlen(string) -1] = '_';
	if( debugFlag == 1) printf("Starting reading\n");
	if( debugFlag == 1) printf("string: %s %lu\n", string, strlen(string));

	int eofFlag = 0;
	while( eofFlag != 1 ){
		/* reading */
		static Coordinate relative(0, 0);
		int runCount = 1;
		int digitSize = 0;

		// check to reload
		if(string[0] == '_') {
			fgets( string, sizeof(string), rleFile);
			string[strlen(string) -1] = '_';
		}
		
		// Find the next tag
		if( sscanf( string, "%d", &runCount) == 1){ //number -> 1, not -> 0
			digitSize = countDigits(runCount);
		}

		char tag = string[digitSize];
		switch(tag){
			case 'o':
				for( int k = 0; k < runCount; k++){
					LifeObject::addCoordinate(relative + centre);
					relative.x++;
				}
				break;
			case 'b':
				relative.x += runCount;
				break;
			case '$':
				relative.x = 0;
				relative.y += runCount;
				break;
			case '!':
				eofFlag = 1;
				break;
			case '#':
				break;
			default:
				printf("%c:",tag);
				printf("ERROR: \"o\", \"b\", or \"$\" are expected right after a number\n");
				exit(1);
		}
		stringShift(digitSize + 1, string);
	}

	LifeObject::write();
	return 0;
}

int countDigits(int num){
	int digitsCounts = 0;
	while(num != 0){
		num = num/10;
		digitsCounts++;
	}
	return digitsCounts;
}

int stringShift(int shiftNum, char string[]){
	int i;
	for( i = 0; i < strlen(string) - shiftNum; i++){
		string[i] = string [i + shiftNum];
	}
	string[i] = '_';

	if(debugFlag == 1) printf("string: %s %lu\n", string, strlen(string));
	return 0;
}
