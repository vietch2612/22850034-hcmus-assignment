// VIQR_UTF8.cpp
// Author: Cao Hoai Viet (Ross)
#include "VIQR_UTF8.h"

#include <string>
#include <unordered_map>
#include <vector>

// These mappings should be in the same length and order
// And should be sorted by the length of the first element in descending order
// Example: "e^`" should be before "e^"
// Original mappings isn't sorted, copied from
// https://github.com/anhskohbo/u-convert/blob/master/src/UConvert.php
std::vector<std::string> viqrChars = {
    "A(`", "A(.", "u*.", "U*.", "u*~", "U*~", "u*?", "U*?", "u*`", "U*`", "u*'",
    "U*'", "o*.", "O*.", "o*~", "O*~", "o*?", "O*?", "o*`", "O*`", "o*'", "O*'",
    "o^.", "O^.", "o^~", "O^~", "o^?", "O^?", "o^`", "O^`", "o^'", "O^'", "e^.",
    "E^.", "e^~", "E^~", "e^?", "E^?", "e^`", "E^`", "e^'", "E^'", "a(.", "a(~",
    "A(~", "a(?", "A(?", "a(`", "A^'", "a^'", "A^`", "a^`", "A^?", "a^?", "A^~",
    "a^~", "A^.", "a^.", "A('", "a('", "A`",  "y~",  "A?",  "a.",  "A.",  "u*",
    "A'",  "U*",  "E.",  "e.",  "E?",  "e?",  "E~",  "e~",  "o*",  "O*",  "u~",
    "U~",  "i~",  "I~",  "dd",  "DD",  "a(",  "A(",  "I?",  "i?",  "I.",  "i.",
    "O.",  "o.",  "O?",  "o?",  "y'",  "u'",  "u`",  "o~",  "o^",  "o'",  "o`",
    "i'",  "i`",  "e^",  "e'",  "e`",  "a~",  "a^",  "a'",  "a`",  "Y'",  "U'",
    "U`",  "O~",  "U.",  "u.",  "U?",  "u?",  "O^",  "O'",  "O`",  "I'",  "I`",
    "E^",  "E'",  "E`",  "A~",  "A^",  "Y`",  "y`",  "Y.",  "y.",  "Y?",  "y?",
    "Y~",  "a?",  "\\."};

// Mapping from VIQR to UTF-8
// Used this tool to convert http://www.enderminh.com/minh/vnconversions.aspx
std::vector<std::string> utf8Chars = {
    "Ằ", "Ặ", "ự", "Ự", "ữ", "Ữ", "ử", "Ử", "ừ", "Ừ", "ứ", "Ứ", "ợ", "Ợ", "ỡ",
    "Ỡ", "ở", "Ở", "ờ", "Ờ", "ớ", "Ớ", "ộ", "Ộ", "ỗ", "Ỗ", "ổ", "Ổ", "ồ", "Ồ",
    "ố", "Ố", "ệ", "Ệ", "ễ", "Ễ", "ể", "Ể", "ề", "Ề", "ế", "Ế", "ặ", "ẵ", "Ẵ",
    "ẳ", "Ẳ", "ằ", "Ấ", "ấ", "Ầ", "ầ", "Ẩ", "ẩ", "Ẫ", "ẫ", "Ậ", "ậ", "Ắ", "ắ",
    "À", "ỹ", "Ả", "ạ", "Ạ", "ư", "Á", "Ư", "Ẹ", "ẹ", "Ẻ", "ẻ", "Ẽ", "ẽ", "ơ",
    "Ơ", "ũ", "Ũ", "ĩ", "Ĩ", "đ", "Đ", "ă", "Ă", "Ỉ", "ỉ", "Ị", "ị", "Ọ", "ọ",
    "Ỏ", "ỏ", "ý", "ú", "ù", "õ", "ô", "ó", "ò", "í", "ì", "ê", "é", "è", "ã",
    "â", "á", "à", "Ý", "Ú", "Ù", "Õ", "Ụ", "ụ", "Ủ", "ủ", "Ô", "Ó", "Ò", "Í",
    "Ì", "Ê", "É", "È", "Ã", "Â", "Ỳ", "ỳ", "Ỵ", "ỵ", "Ỷ", "ỷ", "Ỹ", "ả", ".",
};

std::string viqrToUtf8(const std::string& viqr) {
  std::string utf8;
  for (size_t i = 0; i < viqr.length();) {
    // Check for special characters
    // Like 'a^', 'a~', 'a`', etc.
    bool matched = false;
    for (size_t j = 0; j < viqrChars.size(); ++j) {
      if (viqr.substr(i, viqrChars[j].length()) ==
          viqrChars[j]) {            // Check for match
        utf8 += utf8Chars[j];        // Append the corresponding UTF-8 character
        i += viqrChars[j].length();  // Move to the next character
        matched = true;
        break;
      }
    }

    // If no match is found
    // It means it is a normal character like 'a', 'b', 'c', etc.
    if (!matched) {
      utf8 += viqr[i];  // Append the character as is
      i++;              // Move to the next character
    }
  }

  return utf8;
}

std::string utf8ToViqr(const std::string& utf8) {
  std::string result = "";
  // Loop through utf8 string
  for (size_t i = 0; i < utf8.length(); i++) {
    bool matched = false;
    for (size_t j = 0; j < utf8Chars.size(); j++) {
      // If the UTF8 character is match with the utf8Chars
      if (utf8.substr(i, utf8Chars[j].length()) == utf8Chars[j]) {
        result += viqrChars[j];
        i += utf8Chars[j].length() - 1;
        matched = true;
        break;
      }
    }

    // If no match is found, append the character as is
    if (!matched) {
      result += utf8[i];
    }
  }
  return result;
}