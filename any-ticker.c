#include <stdio.h>
#include <string.h>
#include <math.h>

int append( char *inputFileName, char *outputFileName, int shiftX, int shiftY, int yDirection);
int outputFileInitialise( char *outputFileName);
int debugFlag = 0;

int main(int argc, char *argv[]){
	/* int yEatersCentre = 79; */
	/* int xEatersCentre = 18; */
	/* int yGunCentre = 292; */
	/* int xGunCentre = -5; //Can't be closer than this */
	
	char eaterFileName[100];
	/* set file name here */
	strcpy( eaterFileName, "eater.life");
	int yEaterCentre = -11;
	int xEaterCentre = 4;

	char gunPart1FileName[100];
	/* set file name here */
	strcpy( gunPart1FileName, "ticker.gun.part1.life");
	int xGunPart1Centre = -5; //Can't be closer than this
	int yGunPart1Centre = 88;

	char gunPart2FileName[100];
	/* set file name here */
	strcpy( gunPart2FileName, "ticker.gun.part2.life");
	int xGunPart2Centre = -22; //Can't be closer than this
	int yGunPart2Centre = 85;
	
	char gliderPhase1FileName[100];
	/* set file name here */
	strcpy( gliderPhase1FileName, "glider.phase1.life");
	int xGlider1Centre = -23;
	int yGlider1Centre = 68;
	
	char gliderPhase1DownFileName[100];
	/* set file name here */
	strcpy( gliderPhase1DownFileName, "glider.phase1.down.life");
	int xGlider1DownCentre = -28;
	int yGlider1DownCentre = 53;
	
	char gliderPhase1NwFileName[100];
	/* set file name here */
	strcpy( gliderPhase1NwFileName, "glider.phase1.nw.life");
	int xGlider1NwCentre = -47;
	int yGlider1NwCentre = 57;

	char gliderPhase3UpFileName[100];
	/* set file name here */
	strcpy( gliderPhase3UpFileName, "glider.phase3.up.life");
	int xGlider3UpCentre = -36;
	int yGlider3UpCentre = 69;
	
	char outputFileName[100];
	/* set file name here */	
	strcpy( outputFileName, "any-ticker.life");
	outputFileInitialise( outputFileName);

	/* putting guns and gliders */
	int gunNum = 1;
	for(int i = 0; i < gunNum; i++){
		int yFlag = pow(-1,i );
		int xShift = 115 *(i/2);
		int yShift = 18 * (i/2);
		append( gunPart1FileName, outputFileName, -xGunPart1Centre - xShift, -yGunPart1Centre - yShift, yFlag);
		append( gunPart2FileName, outputFileName, -xGunPart2Centre - xShift, -yGunPart2Centre - yShift, yFlag);
		append( gliderPhase1FileName, outputFileName, -xGlider1Centre - xShift, -yGlider1Centre - yShift, yFlag);
		append( gliderPhase1DownFileName, outputFileName, -xGlider1DownCentre - xShift , -yGlider1DownCentre - yShift, yFlag);
		append( gliderPhase3UpFileName, outputFileName, -xGlider3UpCentre - xShift , -yGlider3UpCentre - yShift, yFlag);
		append( gliderPhase1NwFileName, outputFileName, -xGlider1NwCentre - xShift , -yGlider1NwCentre - yShift, yFlag);
	}
	printf("%d gun(s) put\n", gunNum);

	/* putting eaters */
	int distant = 0;
	distant += 115 *  ( (gunNum - 1) / 2) - ((gunNum -1) / 2) % 2;
	int eaterNum = gunNum + 2;
	for( int i = 0; i < eaterNum; i++){
		int yFlag = pow( -1, ( i+3)/2);
		int negFlag = pow( -1, (i + 2)/2);
		append( eaterFileName, outputFileName, -xEaterCentre - distant, -yEaterCentre - negFlag * 36 * ( (i + 2)/4), yFlag);
	}
	printf("%d eaterss are put\n", eaterNum);

	printf("\nEnd combining with no error\n");
}

int outputFileInitialise( char *outputFileName){
	FILE *outputFile;
	outputFile = fopen( outputFileName, "w");
	if( outputFile == NULL){
		printf("Can't open \"%s\". Try again.\n", outputFileName);
		return 1;
	}else{
		if(debugFlag != 0) printf("\"%s\" is successfully created\n", outputFileName);
	}
	fprintf( outputFile, "#Life 1.06\n");
	fclose( outputFile);

	printf("Initialisation done\n");
	return 0;
}

int append( char *inputFileName, char *outputFileName, int shiftX, int shiftY, int yDirection){
	
	/* opening input file */
	FILE *inputFile;
	inputFile = fopen( inputFileName, "r");
	if( inputFile == NULL){
		printf("Can't open \"%s\". Try again.\n", inputFileName );
		return 1;
	}else{
		if( debugFlag != 0) printf("\"%s\" is successfully opened\n", inputFileName );
	}

	/* opening output file */
	FILE *outputFile;
	outputFile = fopen( outputFileName, "a");
	if( outputFile == NULL){
		printf("Can't open \"%s\". Try again.\n", outputFileName);
		return 1;
	}else{
		if( debugFlag != 0) printf("\"%s\" is successfully opened\n", outputFileName);
	}

	if(debugFlag != 0)printf("start reading %s\n", inputFileName);
	char tempString[1000];
	tempString[0] = '#';
	while( tempString[0] == '#') fgets( tempString, sizeof(tempString), inputFile);
	/* printf("%s\n", tempString); */
	
	int eofFlag =0;
	while( eofFlag != 1){
		int xTemp, yTemp;
		sscanf( tempString, "%d %d", &xTemp, &yTemp);
		fprintf( outputFile, "%d %d\n", xTemp + shiftX, (yTemp + shiftY )*yDirection);
		if( fgets( tempString, sizeof(tempString), inputFile) == NULL){
			eofFlag = 1;
		}else{
			/* printf("%s", tempString); */
		}
	}
	if( debugFlag != 0) printf("end reading \"%s\"\n", inputFileName);
	fclose( inputFile);
	fclose( outputFile);

	return 0;
}
