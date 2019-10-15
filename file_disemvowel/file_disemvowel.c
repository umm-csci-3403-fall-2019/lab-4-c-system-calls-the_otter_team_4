#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

#define BUF_SIZE 1024

// Checks if the provided character is a vowel, lower or upper case
bool isvowel(char const c) 
{
  char cl = tolower(c);
  if(cl == 'a' || cl == 'e' || cl == 'i' || cl == 'o' || cl == 'u') {
    return true;
  } else {
    return false;
  }
}

char *copy_non_vowels(char const *str){
	int i, len, nvlen, pos;

  	char* outstr;
  
  	len = strlen(str) + 1;

  	// non-vowel length
  	nvlen = 0;

  	// Loop through the input string and count the non-vowel characters
  	for(i=0; i<len; ++i) {
    	if(!isvowel(str[i])) {
      	nvlen++;
   		}
  	}

  	outstr = (char*) calloc(nvlen, sizeof(char));

  // Tracks position in output string
  pos = 0;

  // Loops through input string and adds non-vowel characters to output string
  for(i=0; i<len; ++i) {
    if(!isvowel(str[i])) {
      outstr[pos] = str[i];
      pos++;
    }
  }

  return outstr;
}



void disemvowel(FILE* inputFile, FILE* outputFile) {

	// We need memory for our buffer, and we will use the size provided in the orig. code.
	char buff[BUF_SIZE];

	while( fgets(buff, sizeof(buff), inputFile)) {

		char* noVowels = copy_non_vowels(buff);

		fputs(noVowels, outputFile);
		free(noVowels);

	}

	// Dont forget to free these files.
	fclose(inputFile);
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
