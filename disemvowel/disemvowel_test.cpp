#include <gtest/gtest.h>

#include "disemvowel.h"

TEST(Disemvowel, HandleEmptyString) {
  const char* result = disemvowel((char*) "");
  ASSERT_STREQ("", result);
  free((void*)result);
}

TEST(Disemvowel, HandleNoVowels) {
  const char* result = disemvowel((char*) "pqrst");
  ASSERT_STREQ("pqrst", result);
  free((void*)result);
}

TEST(Disemvowel, HandleOnlyVowels) {
  const char* result = disemvowel((char*) "aeiouAEIOUOIEAuoiea");
  ASSERT_STREQ("", result);
  free((void*)result);
}

TEST(Disemvowel, HandleMorrisMinnesota) {
  const char* result = disemvowel((char*) "Morris, Minnesota");
  ASSERT_STREQ("Mrrs, Mnnst", result);
  free((void*)result);
}

TEST(Disemvowel, HandlePunctuation) {
  const char* result = disemvowel((char*) "An (Unexplained) Elephant!");
  ASSERT_STREQ("n (nxplnd) lphnt!", result);
  free((void*)result);
}

TEST(Disemvowel, HandleLongString) {
  char *str;
  int size;
  int i;

  size = 50000;
  str = (char*) calloc(size, sizeof(char));
  str[0] = 'x';
  str[1] = 'y';
  str[2] = 'z';
  for (i = 3; i < size-1; ++i) {
    str[i] = 'a';
  }
  str[size-1] = '\0';
  
  char* result = disemvowel(str);
  ASSERT_STREQ("xyz", result);

  free((void*)result);
  free((void*)str);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
