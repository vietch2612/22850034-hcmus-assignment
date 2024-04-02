#include <gtest/gtest.h>

#include "VIQR_UTF8.h"

TEST(VIQRToUtf8Conversion, BaseCharacters) {
  EXPECT_EQ(viqrToUtf8("a"), "a");
  EXPECT_EQ(viqrToUtf8("ă"), "ă");
}

TEST(VIQRToUtf8Conversion, SpecialCharacters) {
  EXPECT_EQ(viqrToUtf8("dd"), "đ");
}

TEST(VIQRToUtf8Conversion, CharactersWithDiacritics) {
  EXPECT_EQ(viqrToUtf8("a'"), "á");
  EXPECT_EQ(viqrToUtf8("e^`"), "ề");
}

TEST(VIQRToUtf8Conversion, FullParagraph) {
  std::string expected = "Việt Nam đất nước mến yêu";
  std::string actual = viqrToUtf8("Vie^.t Nam dda^'t nu*o*'c me^'n ye^u");
  EXPECT_EQ(actual, expected);
}

TEST(Utf8ToViqrConversion, BaseCharacters) {
  EXPECT_EQ(utf8ToViqr("a"), "a");
  EXPECT_EQ(utf8ToViqr("ă"), "a(");
}

TEST(Utf8ToViqrConversion, SpecialCharacters) {
  EXPECT_EQ(utf8ToViqr("đ"), "dd");
}

TEST(Utf8ToViqrConversion, CharactersWithDiacritics) {
  EXPECT_EQ(utf8ToViqr("á"), "a'");
  EXPECT_EQ(utf8ToViqr("ề"), "e^`");
}

TEST(Utf8ToViqrConversion, FullParagraph) {
  std::string actual = utf8ToViqr("Việt Nam đất nước mến yêu");
  std::string expected = "Vie^.t Nam dda^'t nu*o*'c me^'n ye^u";
  EXPECT_EQ(actual, expected);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
