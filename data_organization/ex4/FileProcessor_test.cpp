// FileProcessor_test.cpp
// Author: Cao Hoai Viet (Ross)
#include "FileProcessor.h"

#include <gtest/gtest.h>

#include <fstream>

// Helper function to write test input file
void writeTestFile(const std::string& filePath, const std::string& content) {
  std::ofstream outFile(filePath);
  ASSERT_TRUE(outFile.is_open());
  outFile << content;
  outFile.close();
}

// Helper function to read test output file
std::string readTestFile(const std::string& filePath) {
  std::ifstream inFile(filePath);
  //   ASSERT_TRUE(inFile.is_open());
  std::string content((std::istreambuf_iterator<char>(inFile)),
                      std::istreambuf_iterator<char>());
  inFile.close();
  return content;
}

TEST(ProcessFileTest, ViqrToUtf8Conversion) {
  // Arrange
  std::string inputFilePath = "in.txt";
  std::string outputFilePath = "out.txt";
  writeTestFile(inputFilePath, "Vie^.t Nam dda^'t nu*o*'c me^'n ye^u");

  // Act
  processFile(1, inputFilePath, outputFilePath);

  // Assert
  std::string expectedOutput =
      "Việt Nam đất nước mến yêu";  // Expected UTF8 output
  ASSERT_EQ(readTestFile(outputFilePath), expectedOutput);
}

TEST(ProcessFileTest, Utf8ToViqrConversion) {
  // Arrange
  std::string inputFilePath = "in.txt";
  std::string outputFilePath = "out.txt";
  writeTestFile(inputFilePath, "Việt Nam đất nước mến yêu");

  // Act
  processFile(2, inputFilePath, outputFilePath);

  // Assert
  std::string expectedOutput =
      "Vie^.t Nam dda^'t nu*o*'c me^'n ye^u";  // Expected VIQR output
  ASSERT_EQ(readTestFile(outputFilePath), expectedOutput);
}

TEST(ProcessFileTest, EscapeCharacters) {
  // Arrange
  std::string inputFilePath = "in.txt";
  std::string outputFilePath = "out.txt";
  writeTestFile(inputFilePath, "Vie^.t Nam dda^'t nu*o*'c me^'n ye^u\\.");

  // Act
  processFile(1, inputFilePath, outputFilePath);

  // Assert
  std::string expectedOutput =
      "Việt Nam đất nước mến yêu.";  // Expected VIQR output
  ASSERT_EQ(readTestFile(outputFilePath), expectedOutput);
}