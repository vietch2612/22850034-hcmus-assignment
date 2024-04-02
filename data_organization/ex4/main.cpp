// main.cpp
// Author: Cao Hoai Viet (Ross)
// Last update: 2024-04-02
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

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <mode> <inputfile> <outputfile >\n ";
    return 1;
  }

  int mode = std::stoi(argv[1]);
  std::string inputFilePath = argv[2];
  std::string outputFilePath = argv[3];

  processFile(mode, inputFilePath, outputFilePath);

  return 0;
}