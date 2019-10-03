#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

void main(FILE* inputFile, FILE* outputFile) {
	char* inputCont;
	char* outputCont;
	int fileCharCount = 0;

	FILE* fp = fopen(inputFile, "r");

	char c;
	for(c = getc(fp); c != EOF; c = getc(fp))
		fileCharCount = fileCharCount + 1;

	print("this is the charCont" + fileCharCount);

	fgets(inputCont, fileCharCount ,inputFile);

	fclose(inputFile);

	printf("Here is actual inputCont");
	printf(inputCont);

	// int charCount = strlen(inputCont);

	// copy_non_vowels(charCount, inputCont, outputCont);
	inputCont > outputFile;
}