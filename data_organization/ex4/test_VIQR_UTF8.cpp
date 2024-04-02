// test_VIQR_UTF8.cpp
// Author: Cao Hoai Viet (Ross)
// Last update: 2024-04-02
#include <gtest/gtest.h>

#include "VIQR_UTF8.h"

// Please remember to switch Unicode precomposed in your Vietnamese input method
// Before type the Vietnamese characters in the string literals

TEST(VIQRToUtf8Conversion, BaseCharacters) {
  EXPECT_EQ(viqrToUtf8("a"), "a");
  EXPECT_EQ(viqrToUtf8("a'"), "á");
}

TEST(VIQRToUtf8Conversion, SpecialCharacters) {
  EXPECT_EQ(viqrToUtf8("dd"), "đ");
}

TEST(VIQRToUtf8Conversion, CharactersWithDiacritics) {
  EXPECT_EQ(viqrToUtf8("a'"), "á");
  EXPECT_EQ(viqrToUtf8("e^`"), "ề");
  EXPECT_EQ(viqrToUtf8("u*'"), "ứ");
}

TEST(VIQRToUtf8Conversion, FullParagraph) {
  std::string expected = "Việt Nam đất nước mến yêu";
  std::string actual = viqrToUtf8("Vie^.t Nam dda^'t nu*o*'c me^'n ye^u");
  EXPECT_EQ(actual, expected);
}

TEST(VIQRToUtf8Conversion, UpperCaseCharacters) {
  std::string expected = "Á Ề Ỉ Ỗ Ử Ỹ";
  std::string actual = viqrToUtf8("A' E^` I? O^~ U*? Y~");
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
