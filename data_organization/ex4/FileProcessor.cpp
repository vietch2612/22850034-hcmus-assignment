// FileProcessor.cpp
// Author: Cao Hoai Viet (Ross)
#include "FileProcessor.h"

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
    outFile << viqrToUtf8(content);
  } else if (mode == 2) {
    outFile << utf8ToViqr(content);
  }
}
