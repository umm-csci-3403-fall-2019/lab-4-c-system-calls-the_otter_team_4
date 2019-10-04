#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

void main(int argc, char *argv[]) {

	FILE *inputFile;
    FILE *outputFile;

	if (argc == 1) {
		inputFile = stdin;
		printf("Only one argument. \n");
		char string[256];
		printf( "Please enter a string. \n" );
		fgets(string, 256, stdin);
		printf(string);
	}

	if (argc == 2) {

		// This buffer might need to be resized for larger files
   		char buffer[190];

   		/* Open file for reading*/
   		inputFile = fopen(argv[1], "r");

	    /* Read and display data */
   		fread(buffer, sizeof(char), 1000, inputFile);
   		printf("%s\n", buffer);
   		fclose(inputFile);

	}

	if (argc == 3) {
		printf("There were 3 args recieved. To be continued...");
	}


}