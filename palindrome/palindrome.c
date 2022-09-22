#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "palindrome.h"

/// Takes in string and returns a string allocated on the heap which is filled with the reverse of the input string. Note that this resulting string must be freed.
char *str_reverse(char const *str) {
  int len, i;
  char *result;

  len = strlen(str);
  result = (char*) calloc(len+1, sizeof(char));
  for (i=0; i<len; ++i) {
    result[i] = str[len-i-1];
  }
  result[len] = '\0';
  
  return result;
}

/// Takes in a string and returns a string containing either "Yes" or "No" allocated on the heap. Note that this resulting string must be freed.
char *palindrome(char const *str) {
  char *rev;
  int i;
  bool result = true;
  char *answer;

  rev = str_reverse(str);
  i = 0;
  
  // Compare `str` and `rev`, setting result to true if they are the same string
  result = strcmp(str, rev) == 0;
  
  // Free the memory allocated by the call to `str_reverse`
  free(rev);

  if (result) {
    answer = (char*) calloc(4, sizeof(char));
    answer[0] = 'Y';
    answer[1] = 'e';
    answer[2] = 's';
    answer[3] = '\0';
  } else {
    answer = (char*) calloc(3, sizeof(char));
    answer[0] = 'N';
    answer[1] = 'o';
    answer[2] = '\0';
  }

  return answer;
}
