#include <gtest/gtest.h>

#include "disemvowel.h"

TEST(Disemvowel, HandleEmptyString) {
  char* disemvoweled = disemvowel((char*) "");
  ASSERT_STREQ("", disemvoweled);
  free(disemvoweled);
}

TEST(Disemvowel, HandleNoVowels) {
  char* disemvoweled = disemvowel((char*) "pqrst");
  ASSERT_STREQ("pqrst", disemvoweled);
  free(disemvoweled);
}

TEST(Disemvowel, HandleOnlyVowels) {
  char* disemvoweled = disemvowel((char*) "aeiouAEIOUOIEAuoiea");
  ASSERT_STREQ("", disemvoweled);
  free(disemvoweled);
}

TEST(Disemvowel, HandleMorrisMinnesota) {
  char* disemvoweled = disemvowel((char*) "Morris, Minnesota");
  ASSERT_STREQ("Mrrs, Mnnst", disemvoweled);
  free(disemvoweled);
}

TEST(Disemvowel, HandlePunctuation) {
  char* disemvoweled = disemvowel((char*) "An (Unexplained) Elephant!");
  ASSERT_STREQ("n (nxplnd) lphnt!", disemvoweled);
  free(disemvoweled);
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
  
  char* disemvoweled = disemvowel(str);

  ASSERT_STREQ("xyz", disemvoweled);

  free(str);

  free(disemvoweled);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
