// VIQR_UTF8.cpp
// Author: Cao Hoai Viet (Ross)
#include "VIQR_UTF8.h"

#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> viqrChars = {
    "A`",  "A'",  "A^",  "A~",  "E`",  "E'",  "E^",  "I`",  "I'",  "O`",  "O'",
    "O^",  "O~",  "U`",  "U'",  "Y'",  "a`",  "a'",  "a^",  "a~",  "e`",  "e'",
    "e^",  "i`",  "i'",  "o`",  "o'",  "o^",  "o~",  "u`",  "u'",  "y'",  "A(",
    "a(",  "DD",  "dd",  "I~",  "i~",  "U~",  "u~",  "O*",  "o*",  "U*",  "u*",
    "A.",  "a.",  "A?",  "a?",  "A^'", "a^'", "A^`", "a^`", "A^?", "a^?", "A^~",
    "a^~", "A^.", "a^.", "A('", "a('", "A(`", "a(`", "A(?", "a(?", "A(~", "a(~",
    "A(.", "a(.", "E.",  "e.",  "E?",  "e?",  "E~",  "e~",  "E^'", "e^'", "E^`",
    "e^`", "E^?", "e^?", "E^~", "e^~", "E^.", "e^.", "I?",  "i?",  "I.",  "i.",
    "O.",  "o.",  "O?",  "o?",  "O^'", "o^'", "O^`", "o^`", "O^?", "o^?", "O^~",
    "o^~", "O^.", "o^.", "O*'", "o*'", "O*`", "o*`", "O*?", "o*?", "O*~", "o*~",
    "O*.", "o*.", "U.",  "u.",  "U?",  "u?",  "U*'", "u*'", "U*`", "u*`", "U*?",
    "u*?", "U*~", "u*~", "U*.", "u*.", "Y`",  "y`",  "Y.",  "y.",  "Y?",  "y?",
    "Y~",  "y~"};

std::vector<std::string> utf8Chars = {
    "À", "Á", "Â", "Ã", "È", "É", "Ê", "Ì", "Í", "Ò", "Ó", "Ô", "Õ", "Ù", "Ú",
    "Ý", "à", "á", "â", "ã", "è", "é", "ê", "ì", "í", "ò", "ó", "ô", "õ", "ù",
    "ú", "ý", "Ă", "ă", "Ð", "đ", "Ĩ", "ĩ", "Ũ", "ũ", "Ơ", "ơ", "Ư", "ư", "Ạ",
    "ạ", "Ả", "ả", "Ấ", "ấ", "Ầ", "ầ", "Ẩ", "ẩ", "Ẫ", "ẫ", "Ậ", "ậ", "Ắ", "ắ",
    "Ằ", "ằ", "Ẳ", "ẳ", "Ẵ", "ẵ", "Ặ", "ặ", "Ẹ", "ẹ", "Ẻ", "ẻ", "Ẽ", "ẽ", "Ế",
    "ế", "Ề", "ề", "Ể", "ể", "Ễ", "ễ", "Ệ", "ệ", "Ỉ", "ỉ", "Ị", "ị", "Ọ", "ọ",
    "Ỏ", "ỏ", "Ố", "ố", "Ồ", "ồ", "Ổ", "ổ", "Ỗ", "ỗ", "Ộ", "ộ", "Ớ", "ớ", "Ờ",
    "ờ", "Ở", "ở", "Ỡ", "ỡ", "Ợ", "ợ", "Ụ", "ụ", "Ủ", "ủ", "Ứ", "ứ", "Ừ", "ừ",
    "Ử", "ử", "Ữ", "ữ", "Ự", "ự", "Ỳ", "ỳ", "Ỵ", "ỵ", "Ỷ", "ỷ", "Ỹ", "ỹ"};

std::string viqrToUtf8(const std::string& viqr) {
  // Create a mapping from VIQR to UTF-8
  std::unordered_map<std::string, std::string> viqrToUtf8Map;
  for (size_t i = 0; i < viqrChars.size(); ++i) {
    viqrToUtf8Map[viqrChars[i]] = utf8Chars[i];
  }

  std::string utf8;
  for (size_t i = 0; i < viqr.length();) {
    bool matched = false;

    // Check for multi-character sequences first (e.g., "dd")
    for (const auto& pair : viqrToUtf8Map) {
      if (viqr.substr(i, pair.first.length()) == pair.first) {
        utf8 += pair.second;
        i += pair.first.length();
        matched = true;
        break;
      }
    }

    // If no multi-character sequence matched, process single characters
    if (!matched) {
      auto singleChar = viqrToUtf8Map.find(std::string(1, viqr[i]));
      if (singleChar != viqrToUtf8Map.end()) {
        utf8 += singleChar->second;
      } else {
        utf8 += viqr[i];
      }
      ++i;
    }
  }
  return utf8;
}

std::string utf8ToViqr(const std::string& utf8) {
  std::string result = utf8;
  for (size_t i = 0; i < utf8Chars.size(); ++i) {
    std::string::size_type pos = 0;
    while ((pos = result.find(utf8Chars[i], pos)) != std::string::npos) {
      result.replace(pos, utf8Chars[i].length(), viqrChars[i]);
      pos += viqrChars[i].length();
    }
  }
  return result;
}