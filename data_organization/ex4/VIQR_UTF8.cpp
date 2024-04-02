// VIQR_UTF8.cpp
// Author: Cao Hoai Viet (Ross)
// Last update: 2024-04-02
#include "VIQR_UTF8.h"

#include <unordered_map>

// Mapping from VIQR to UTF-8 characters.
std::unordered_map<std::string, std::string> viqrToUtf8Map = {
    // Base characters
    {"a", "a"},
    {"ă", "ă"},
    {"â", "â"},
    {"e", "e"},
    {"ê", "ê"},
    {"i", "i"},
    {"o", "o"},
    {"ô", "ô"},
    {"ơ", "ơ"},
    {"u", "u"},
    {"ư", "ư"},
    {"y", "y"},

    // Capitals
    {"A", "A"},
    {"Ă", "Ă"},
    {"Â", "Â"},
    {"E", "E"},
    {"Ê", "Ê"},
    {"I", "I"},
    {"O", "O"},
    {"Ô", "Ô"},
    {"Ơ", "Ơ"},
    {"U", "U"},
    {"Ư", "Ư"},
    {"Y", "Y"},

    // Diacritics and special characters
    // Diacritic marks (combining characters)
    {"'", "\u0301"},  // sắc
    {"`", "\u0300"},  // huyền
    {"?", "\u0309"},  // hỏi
    {"~", "\u0303"},  // ngã
    {".", "\u0323"},  // nặng
    {"^", "\u0302"},  // â, ô
    {"*", "\u031B"},  // ư, ơ

    // Additional mappings for specific combinations
    {"dd", "đ"},
    {"DD", "Đ"}};

std::string viqrToUtf8(const std::string& viqr) {
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

std::unordered_map<std::string, std::string> utf8ToViqrMap = {
    // Special characters
    {"đ", "dd"},
    {"Đ", "DD"},
    // Vowels with diacritics
    {"á", "a'"},
    {"à", "a`"},
    {"ả", "a?"},
    {"ã", "a~"},
    {"ạ", "a."},
    {"â", "a^"},
    {"ấ", "a^'"},
    {"ầ", "a^`"},
    {"ẩ", "a^?"},
    {"ẫ", "a^~"},
    {"ậ", "a^."},
    {"ă", "a("},
    {"ắ", "a('"},
    {"ằ", "a(`"},
    {"ẳ", "a(?"},
    {"ẵ", "a(~"},
    {"ặ", "a(."},
    // E, e
    {"é", "e'"},
    {"è", "e`"},
    {"ẻ", "e?"},
    {"ẽ", "e~"},
    {"ẹ", "e."},
    {"ê", "e^"},
    {"ế", "e^'"},
    {"ề", "e^`"},
    {"ể", "e^?"},
    {"ễ", "e^~"},
    {"ệ", "e^."},
    // I, i
    {"í", "i'"},
    {"ì", "i`"},
    {"ỉ", "i?"},
    {"ĩ", "i~"},
    {"ị", "i."},
    // O, o
    {"ó", "o'"},
    {"ò", "o`"},
    {"ỏ", "o?"},
    {"õ", "o~"},
    {"ọ", "o."},
    {"ô", "o^"},
    {"ố", "o^'"},
    {"ồ", "o^`"},
    {"ổ", "o^?"},
    {"ỗ", "o^~"},
    {"ộ", "o^."},
    {"ơ", "o+"},
    {"ớ", "o+'"},
    {"ờ", "o+`"},
    {"ở", "o+?"},
    {"ỡ", "o+~"},
    {"ợ", "o+."},
    // U, u
    {"ú", "u'"},
    {"ù", "u`"},
    {"ủ", "u?"},
    {"ũ", "u~"},
    {"ụ", "u."},
    {"ư", "u+"},
    {"ứ", "u+'"},
    {"ừ", "u+`"},
    {"ử", "u+?"},
    {"ữ", "u+~"},
    {"ự", "u+."},
    // Y, y
    {"ý", "y'"},
    {"ỳ", "y`"},
    {"ỷ", "y?"},
    {"ỹ", "y~"},
    {"ỵ", "y."},
    // A, a
    {"Á", "A'"},
    {"À", "A`"},
    {"Ả", "A?"},
    {"Ã", "A~"},
    {"Ạ", "A."},
    {"Â", "A^"},
    {"Ấ", "A^'"},
    {"Ầ", "A^`"},
    {"Ẩ", "A^?"},
    {"Ẫ", "A^~"},
    {"Ậ", "A^."},
    {"Ă", "A("},
    {"Ắ", "A('"},
    {"Ằ", "A(`"},
    {"Ẳ", "A(?"},
    {"Ẵ", "A(~"},
    {"Ặ", "A(."},
    // E, e
    {"É", "E'"},
    {"È", "E`"},
    {"Ẻ", "E?"},
    {"Ẽ", "E~"},
    {"Ẹ", "E."},
    {"Ê", "E^"},
    {"Ế", "E^'"},
    {"Ề", "E^`"},
    {"Ể", "E^?"},
    {"Ễ", "E^~"},
    {"Ệ", "E^."},
    // I, i
    {"Í", "I'"},
    {"Ì", "I`"},
    {"Ỉ", "I?"},
    {"Ĩ", "I~"},
    {"Ị", "I."},
    // O, o
    {"Ó", "O'"},
    {"Ò", "O`"},
    {"Ỏ", "O?"},
    {"Õ", "O~"},
    {"Ọ", "O."},
    {"Ô", "O^"},
    {"Ố", "O^'"},
    {"Ồ", "O^`"},
    {"Ổ", "O^?"},
    {"Ỗ", "O^~"},
    {"Ộ", "O^."},
    {"Ơ", "O+"},
    {"Ớ", "O+'"},
    {"Ờ", "O+`"},
    {"Ở", "O+?"},
    {"Ỡ", "O+~"},
    {"Ợ", "O+."},
    // U, u
    {"Ú", "U'"},
    {"Ù", "U`"},
    {"Ủ", "U?"},
    {"Ũ", "U~"},
    {"Ụ", "U."},
    {"Ư", "U+"},
    {"Ứ", "U+'"},
    {"Ừ", "U+`"},
    {"Ử", "U+?"},
    {"Ữ", "U+~"},
    {"Ự", "U+."},
    // Y, y
    {"Ý", "Y'"},
    {"Ỳ", "Y`"},
    {"Ỷ", "Y?"},
    {"Ỹ", "Y~"},
    {"Ỵ", "Y."},
};

std::string utf8CharacterToViqr(const std::string& character) {
  if (utf8ToViqrMap.find(character) != utf8ToViqrMap.end()) {
    return utf8ToViqrMap[character];
  }
  return character;  // Return the character itself if not found in the map
}

std::string utf8ToViqr(const std::string& utf8String) {
  std::string viqrString;
  for (size_t i = 0; i < utf8String.length();) {
    std::string utf8Char;
    unsigned char lead = utf8String[i];
    if (lead < 0x80) {
      utf8Char = utf8String.substr(i, 1);
      i += 1;
    } else if ((lead >> 5) == 0x6) {
      utf8Char = utf8String.substr(i, 2);
      i += 2;
    } else if ((lead >> 4) == 0xE) {
      utf8Char = utf8String.substr(i, 3);
      i += 3;
    } else if ((lead >> 3) == 0x1E) {
      utf8Char = utf8String.substr(i, 4);
      i += 4;
    } else {
      // Error handling or skip
      i += 1;  // Skipping invalid starts, for simplicity
    }
    viqrString += utf8CharacterToViqr(utf8Char);
  }
  return viqrString;
}
