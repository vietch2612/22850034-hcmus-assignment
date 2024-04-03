// test_VIQR_UTF8.cpp
// Author: Cao Hoai Viet (Ross)
#include "VIQR_UTF8.h"

#include <gtest/gtest.h>

// Please remember to switch Unicode precomposed in your Vietnamese input method
// Before type the Vietnamese characters in the string literals

// GoogleTest: https://github.com/google/googletest

TEST(VIQRToUtf8Conversion, BaseCharacters) {
  EXPECT_EQ(viqrToUtf8("a"), "a");
  EXPECT_EQ(viqrToUtf8("a'"), "á");
  EXPECT_EQ(viqrToUtf8("a("), "ă");
  EXPECT_EQ(viqrToUtf8("a~"), "ã");
  EXPECT_EQ(viqrToUtf8("a^"), "â");
  EXPECT_EQ(viqrToUtf8("a`"), "à");
  EXPECT_EQ(viqrToUtf8("A"), "A");
  EXPECT_EQ(viqrToUtf8("A'"), "Á");
}

TEST(VIQRToUtf8Conversion, SpecialCharacters) {
  EXPECT_EQ(viqrToUtf8("dd"), "đ");
  EXPECT_EQ(viqrToUtf8("DD"), "Đ");
}

TEST(VIQRToUtf8Conversion, CharactersWithDiacritics) {
  EXPECT_EQ(viqrToUtf8("a'"), "á");
  EXPECT_EQ(viqrToUtf8("e^`"), "ề");
  EXPECT_EQ(viqrToUtf8("u*'"), "ứ");
  EXPECT_EQ(viqrToUtf8("U*~"), "Ữ");
  EXPECT_EQ(viqrToUtf8("o*?"), "ở");
  EXPECT_EQ(viqrToUtf8("O*`"), "Ờ");
  EXPECT_EQ(viqrToUtf8("o^'"), "ố");
  EXPECT_EQ(viqrToUtf8("O^`"), "Ồ");
}

TEST(VIQRToUtf8Conversion, FullParagraph) {
  EXPECT_EQ(viqrToUtf8("Vie^.t Nam dda^'t nu*o*'c me^'n ye^u"),
            "Việt Nam đất nước mến yêu");
  EXPECT_EQ(viqrToUtf8("Cao Hoa`i Vie^.t"), "Cao Hoài Việt");
  EXPECT_EQ(viqrToUtf8("DDa.i ho.c Khoa ho.c tu*. nhie^n TP.HCM"),
            "Đại học Khoa học tự nhiên TP.HCM");
};

TEST(VIQRToUtf8Conversion, EscapeCharacters) {
  EXPECT_EQ(viqrToUtf8("ye^u\."), "yêu.");
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
