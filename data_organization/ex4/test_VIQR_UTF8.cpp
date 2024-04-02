#include "VIQR_UTF8.h"

#include <gtest/gtest.h>

TEST(VIQRToUtf8Conversion, BaseCharacters) {
  EXPECT_EQ(viqrToUtf8("a"), "a");
  EXPECT_EQ(viqrToUtf8("ă"), "ă");
  // Add more base character tests here
}

TEST(VIQRToUtf8Conversion, SpecialCharacters) {
  EXPECT_EQ(viqrToUtf8("dd"), "đ");
  // Add more special character tests here
}

TEST(VIQRToUtf8Conversion, CharactersWithDiacritics) {
  EXPECT_EQ(viqrToUtf8("a'"), "á");
  EXPECT_EQ(viqrToUtf8("e^`"), "ề");
  // Add more diacritics tests here
}

TEST(Utf8ToViqrConversion, BaseCharacters) {
  EXPECT_EQ(utf8ToViqr("a"), "a");
  EXPECT_EQ(utf8ToViqr("ă"), "a(");
  // Add more base character tests here
}

TEST(Utf8ToViqrConversion, SpecialCharacters) {
  EXPECT_EQ(utf8ToViqr("đ"), "dd");
  // Add more special character tests here
}

TEST(Utf8ToViqrConversion, CharactersWithDiacritics) {
  EXPECT_EQ(utf8ToViqr("á"), "a'");
  EXPECT_EQ(utf8ToViqr("ề"), "e^`");
  // Add more diacritics tests here
}

// The main function running the tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
