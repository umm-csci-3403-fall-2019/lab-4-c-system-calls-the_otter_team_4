#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

#define BUF_SIZE 1024

// Checks if the provided character is a vowel, lower or upper case
bool isvowel(char const c) {
  char cl = tolower(c);
  if(cl == 'a' || cl == 'e' || cl == 'i' || cl == 'o' || cl == 'u') {
    return true;
  } else {
    return false;
  }
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf){
	int i, len, nvlen, pos;
	
	len = strlen(in_buf) + 1;
	// non-vowel length
	nvlen = 0;

	// Loop through the input string and count the non-vowel characters
	for(i=0; i<len; ++i) {
		if(!isvowel(in_buf[i])) {
			nvlen++;
		}
	}
	
	//out_buf = (char*) calloc(nvlen, sizeof(char));
	
	// Tracks position in output string
	pos = 0;
	
	// Loops through input string and adds non-vowel characters to output string
	for(i=0; i<len; ++i) {
		if(!isvowel(in_buf[i])) {
			out_buf[pos] = in_buf[i];
			pos++;
		}
	}

	return nvlen;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
	char * buffer = calloc(BUF_SIZE, sizeof(char));
	char * out_buf = calloc(BUF_SIZE, sizeof(char));
	//long length;

	while( fread(buffer, sizeof(char), BUF_SIZE, inputFile) != 0){
		int nvlen = copy_non_vowels(BUF_SIZE, buffer, out_buf);
		fwrite(out_buf, sizeof(char), nvlen, outputFile);
	}

	free(buffer);
	free(out_buf);

  	fclose (inputFile);
  	fclose(outputFile);

  

}

// Takes a string and returns a new string pointer with the vowels removed
// char *disemvowel(FILE* inputFile, FILE* outputFile) {
//   return 
// }
void main(int argc, char *argv[]) {

	FILE *inputFile;
    FILE *outputFile;

	if (argc == 1) {
		inputFile = stdin;
		outputFile = stdout;

	}

	if (argc == 2) {
   		/* Open file for reading*/
   		inputFile = fopen(argv[1], "r");
   		outputFile = stdout;

	}

	if (argc == 3) {
		inputFile = fopen(argv[1], "r");

		/* Open file for writing */
		outputFile = fopen(argv[2], "w");

	}

	disemvowel(inputFile, outputFile);

}
