#include <stdlib.h>
#include <string.h>

#include "disemvowel.h"

char *disemvowel(char *str) {
  // Allocate space for the result with the same length as the input string plus one for the null terminator
  char* result = (char*)calloc(strlen(str) + 1, 1);

  // Index into the result string
  unsigned int i = 0;

  // Iterate over each character of the input string
  do {
    // If it is a vowel, go to the next character
    switch (*str) {
      case 'a': case 'A':
      case 'e': case 'E':
      case 'i': case 'I':
      case 'o': case 'O':
      case 'u': case 'U':
        break;
      // Otherwise, copy the character to the output
      default:
        result[i++] = *str;
        break;
    }
  }
  while (*(str++));

  return result;
}
