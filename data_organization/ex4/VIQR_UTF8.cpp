// VIQR_UTF8.cpp
// Author: Cao Hoai Viet (Ross)
#include "VIQR_UTF8.h"

#include <string>
#include <unordered_map>
#include <vector>

// These mappings should be in the same length and order
// And should be sorted by the length of the first element in descending order
// Example: "e^`" should be before "e^"
// I did not sort it on runtime to increase performance
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
    "Y~",  "a?",
};

std::vector<std::string> utf8Chars = {
    "Ằ", "Ặ", "ự", "Ự", "ữ", "Ữ", "ử", "Ử", "ừ", "Ừ", "ứ", "Ứ", "ợ", "Ợ", "ỡ",
    "Ỡ", "ở", "Ở", "ờ", "Ờ", "ớ", "Ớ", "ộ", "Ộ", "ỗ", "Ỗ", "ổ", "Ổ", "ồ", "Ồ",
    "ố", "Ố", "ệ", "Ệ", "ễ", "Ễ", "ể", "Ể", "ề", "Ề", "ế", "Ế", "ặ", "ẵ", "Ẵ",
    "ẳ", "Ẳ", "ằ", "Ấ", "ấ", "Ầ", "ầ", "Ẩ", "ẩ", "Ẫ", "ẫ", "Ậ", "ậ", "Ắ", "ắ",
    "À", "ỹ", "Ả", "ạ", "Ạ", "ư", "Á", "Ư", "Ẹ", "ẹ", "Ẻ", "ẻ", "Ẽ", "ẽ", "ơ",
    "Ơ", "ũ", "Ũ", "ĩ", "Ĩ", "đ", "Ð", "ă", "Ă", "Ỉ", "ỉ", "Ị", "ị", "Ọ", "ọ",
    "Ỏ", "ỏ", "ý", "ú", "ù", "õ", "ô", "ó", "ò", "í", "ì", "ê", "é", "è", "ã",
    "â", "á", "à", "Ý", "Ú", "Ù", "Õ", "Ụ", "ụ", "Ủ", "ủ", "Ô", "Ó", "Ò", "Í",
    "Ì", "Ê", "É", "È", "Ã", "Â", "Ỳ", "ỳ", "Ỵ", "ỵ", "Ỷ", "ỷ", "Ỹ", "ả",
};

std::string viqrToUtf8(const std::string& viqr) {
  std::string utf8;
  for (size_t i = 0; i < viqr.length();) {  // Iterate through the VIQR string
    bool matched = false;

    for (size_t j = 0; j < viqrChars.size();
         ++j) {  // Iterate through the VIQR characters
      if (viqr.substr(i, viqrChars[j].length()) ==
          viqrChars[j]) {            // Check if the VIQR character is found
        utf8 += utf8Chars[j];        // Append the corresponding UTF-8 character
        i += viqrChars[j].length();  // Move to the next character
        matched = true;              // Set the matched flag to true
        break;
      }
    }

    if (!matched) {     // If the VIQR character is not found
      utf8 += viqr[i];  // Append the character itself
      i++;              // Move to the next character
    }
  }

  return utf8;
}

std::string utf8ToViqr(const std::string& utf8) {
  std::string result = utf8;  // The result string
  for (size_t i = 0; i < utf8Chars.size();
       ++i) {                        // Iterate through the UTF-8 characters
    std::string::size_type pos = 0;  // The position of the found character
    while ((pos = result.find(utf8Chars[i], pos)) !=
           std::string::npos) {  // Find the UTF-8 character
      result.replace(
          pos, utf8Chars[i].length(),
          viqrChars[i]);  // Replace the UTF-8 character with the VIQR character
      pos += viqrChars[i].length();  // Move to the next character
    }
  }

  return result;
}