#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

void main(char* input) {
	// char* inputCont;
	// int fileCharCount = 0;

	FILE *fp = fopen(input, "r");
	input = calloc(10, sizeof(char));
	// char c;
	// for(c = getc(fp); c != EOF; c = getc(fp))
	// 	fileCharCount = fileCharCount + 1;

	// printf("this is the charCont" + fileCharCount);

	// inputCont = (char*) calloc(10, sizeof(char));

	// fgets(inputCont, fileCharCount ,fp);

	fclose(fp);

	printf("Here is actual inputCont");
	printf(input);

	free(input);
	// free(inputCont);

	// int charCount = strlen(inputCont);

	// copy_non_vowels(charCount, inputCont, outputCont);
	// inputCont > outputFile;
}