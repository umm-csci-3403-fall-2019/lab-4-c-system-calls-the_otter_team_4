#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "disemvowel.h"

// Checks if the provided character is a vowel, lower or upper case
bool isvowel(char const c) {
  char cl = tolower(c);
  if(cl == 'a' || cl == 'e' || cl == 'i' || cl == 'o' || cl == 'u') {
    return true;
  } else {
    return false;
  }
}

// Takes a string and returns a new string pointer with the vowels removed
char *disemvowel(char const *str) {
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
