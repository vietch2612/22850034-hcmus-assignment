#include "VIQR_UTF8.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::string> viqr_to_utf8_map = {
    // A, a
    {"a", "a"},
    {"a'", "á"},
    {"a`", "à"},
    {"a?", "ả"},
    {"a~", "ã"},
    {"a.", "ạ"},
    {"a^", "â"},
    {"a^'", "ấ"},
    {"a^`", "ầ"},
    {"a^?", "ẩ"},
    {"a^~", "ẫ"},
    {"a^.", "ậ"},
    {"a(", "ă"},
    {"a('", "ắ"},
    {"a(`", "ằ"},
    {"a(?", "ẳ"},
    {"a(~", "ẵ"},
    {"a(.", "ặ"},
    // E, e
    {"e", "e"},
    {"e'", "é"},
    {"e`", "è"},
    {"e?", "ẻ"},
    {"e~", "ẽ"},
    {"e.", "ẹ"},
    {"e^", "ê"},
    {"e^'", "ế"},
    {"e^`", "ề"},
    {"e^?", "ể"},
    {"e^~", "ễ"},
    {"e^.", "ệ"},
    // I, i
    {"i", "i"},
    {"i'", "í"},
    {"i`", "ì"},
    {"i?", "ỉ"},
    {"i~", "ĩ"},
    {"i.", "ị"},
    // O, o
    {"o", "o"},
    {"o'", "ó"},
    {"o`", "ò"},
    {"o?", "ỏ"},
    {"o~", "õ"},
    {"o.", "ọ"},
    {"o^", "ô"},
    {"o^'", "ố"},
    {"o^`", "ồ"},
    {"o^?", "ổ"},
    {"o^~", "ỗ"},
    {"o^.", "ộ"},
    {"o+", "ơ"},
    {"o+'", "ớ"},
    {"o+`", "ờ"},
    {"o+?", "ở"},
    {"o+~", "ỡ"},
    {"o+.", "ợ"},
    {"o*", "ơ"},
    {"o*'", "ớ"},
    {"o*`", "ờ"},
    {"o*?", "ở"},
    {"o*~", "ỡ"},
    // U, u
    {"u", "u"},
    {"u'", "ú"},
    {"u`", "ù"},
    {"u?", "ủ"},
    {"u~", "ũ"},
    {"u.", "ụ"},
    {"u*", "ư"},
    {"u*'", "ứ"},
    {"u*`", "ừ"},
    {"u*?", "ử"},
    {"u*~", "ữ"},
    {"u+", "ư"},
    {"u+'", "ứ"},
    {"u+`", "ừ"},
    {"u+?", "ử"},
    {"u+~", "ữ"},
    {"u+.", "ự"},
    // Y, y
    {"y", "y"},
    {"y'", "ý"},
    {"y`", "ỳ"},
    {"y?", "ỷ"},
    {"y~", "ỹ"},
    {"y.", "ỵ"},
    // D, d
    {"dd", "đ"},
    {"DD", "Đ"}};

std::unordered_map<std::string, std::string> utf8_to_viqr_map = {
    // A, a
    {"a", "a"},
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
    {"e", "e"},
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
    {"i", "i"},
    {"í", "i'"},
    {"ì", "i`"},
    {"ỉ", "i?"},
    {"ĩ", "i~"},
    {"ị", "i."},
    // O, o
    {"o", "o"},
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
    {"o*", "ơ"},
    {"o*'", "ớ"},
    {"o*`", "ờ"},
    {"o*?", "ở"},
    {"o*~", "ỡ"},
    // U, u
    {"u", "u"},
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
    {"u*", "ư"},
    {"u*'", "ứ"},
    {"u*`", "ừ"},
    {"u*?", "ử"},
    {"u*~", "ữ"},
    // Y, y
    {"y", "y"},
    {"ý", "y'"},
    {"ỳ", "y`"},
    {"ỷ", "y?"},
    {"ỹ", "y~"},
    {"ỵ", "y."},
    // D, d
    {"đ", "dd"},
    {"Đ", "DD"}};

std::vector<std::pair<std::string, std::string>> sorted_pairs(
    utf8_to_viqr_map.begin(), utf8_to_viqr_map.end());

// Sort the vector by the length of the first element (the VIQR string) in
// Descending order
bool compare(const std::pair<std::string, std::string> &a,
             const std::pair<std::string, std::string> &b) {
  return a.first.length() > b.first.length();
}

// Sort the vector of pairs by the length of the first element (the VIQR string)
void sort_pairs() {
  std::sort(sorted_pairs.begin(), sorted_pairs.end(), compare);
}

std::string viqr_to_utf8(const std::string &utf8) {
  sort_pairs();
  std::string output;
  for (size_t i = 0; i < utf8.length();) {
    bool converted = false;
    for (const auto &pair : sorted_pairs) {
      if (utf8.substr(i, pair.second.length()) == pair.second) {
        output += pair.first;
        i += pair.second.length();
        converted = true;
        break;
      }
    }
    if (!converted) {
      output += utf8[i++];
    }
  }
  return output;
}

std::string utf8_to_viqr(const std::string &utf8) {
  std::string output;
  std::string key = "";
  for (size_t i = 0; i < utf8.size(); i++) {
    bool converted = false;
    for (const auto &pair : utf8_to_viqr_map) {
      if (utf8.substr(i, pair.first.length()) == pair.first) {
        output += pair.second;
        i += pair.first.length() - 1;
        converted = true;
        break;
      }
    }
    if (!converted) {
      output += utf8[i];
    }
  }
  return output;
};
