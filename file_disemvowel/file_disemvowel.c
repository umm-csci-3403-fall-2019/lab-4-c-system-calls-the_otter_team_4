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
	char* outstr;
	
	char* instr = in_buf;
	len = strlen(instr) + 1;
	// non-vowel length
	nvlen = 0;

	// Loop through the input string and count the non-vowel characters
	for(i=0; i<len; ++i) {
		if(!isvowel(instr[i])) {
			nvlen++;
		}
	}
	
	outstr = (char*) calloc(nvlen, sizeof(char));
	
	// Tracks position in output string
	pos = 0;
	
	// Loops through input string and adds non-vowel characters to output string
	for(i=0; i<len; ++i) {
		if(!isvowel(instr[i])) {
			outstr[pos] = instr[i];
			pos++;
		}
	}

	out_buf = outstr;
	return nvlen;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
	char * buffer = 0;
	long length;

	fseek (inputFile, 0, SEEK_END);
	length = ftell (inputFile);

  	fseek (inputFile, 0, SEEK_SET);
  	buffer = malloc (length);

  	if (buffer)
  	{
    	fread (buffer, 1, length, inputFile);
  	}

  	fclose (inputFile);

  	char * out_buf;

  	int nvlen = copy_non_vowels(length, buffer, out_buf);

  	printf(out_buf);

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
