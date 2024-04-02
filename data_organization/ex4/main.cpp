#include <fstream>
#include <iostream>
#include <string>

#include "VIQR_UTF8.h"

void processFile(int mode, const std::string& inputFilePath,
                 const std::string& outputFilePath) {
  std::ifstream inFile(inputFilePath, std::ios::binary);
  std::ofstream outFile(outputFilePath, std::ios::binary);
  std::string content((std::istreambuf_iterator<char>(inFile)),
                      std::istreambuf_iterator<char>());

  if (mode == 1) {
    outFile << viqr_to_utf8(content);
  } else if (mode == 2) {
    outFile << utf8_to_viqr(content);
  }
}

// int main(int argc, char* argv[]) {
//   if (argc != 4) {
//     std::cerr << "Usage: " << argv[0] << " <mode> <inputfile>
//     <outputfile>\n"; return 1;
//   }
//
//   int mode = std::stoi(argv[1]);
//   std::string inputFilePath = argv[2];
//   std::string outputFilePath = argv[3];
//
//   processFile(mode, inputFilePath, outputFilePath);
//
//   return 0;
// }
//

int main() {
  std::string test = "Vie^.t Nam dda^'t nu*o*'c me^'n ye^u";
  // std::string test = "a^'";
  std::string utf8 = viqr_to_utf8(test);
  std::cout << utf8 << std::endl;
  return 0;
}
