// main.cpp
// Author: Cao Hoai Viet (Ross)
#include <fstream>
#include <iostream>
#include <string>

#include "FileProcessor.h"
#include "VIQR_UTF8.h"

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