#include <fstream>
#include <iostream>

struct AdjacencyList {
  int vertices;
  int **matrix;

  void readAdjacencyList(std::string fileName) {
    std::ifstream file(fileName);

    // Exit early if the file is not exist
    if (!file.good()) {
      std::cout << "Input file is not exist!" << std::endl;
      std::exit(1);
    }

    if (file.is_open()) {
      std::string line;
      for (int i = 0; std::getline(file, line); i++) {
        // Get the number of vertices in the first line

        if (i == 0) {
          int n = atoi(line.c_str());
          // Exit early if the number of vertices isn't met the requirement
          if (n <= 2) {
            std::cout << "Number of vertices should be greater than 2!"
                      << std::endl;
            exit(1);
          }
          this->vertices = n;
          // Initialize rows of the matrix
          this->matrix = new int *[this->vertices];
          continue;
        }

        // Insert value into the matrix by row number = i-1
        // Because the first row is number of vertices
        int k = 0;
        int row_number = i - 1;
        int number_of_vertex = line[0] - '0';

        // Initialize the size of each row
        // Each row contains the number of adjacent edges of the vertex
        // So that means we have to increase the size by 1
        int size = number_of_vertex + 1;
        this->matrix[row_number] = new int[size];

        // Loop through the string characters
        // If the character != space -> convert to int then push to the array
        for (int j = 0; j < line.length(); j++) {
          if (line[j] != ' ') {
            this->matrix[row_number][k] = line[j] - '0';
            k++;
          }
        }
      }
      file.close();
    }
  }
};

struct AdjacencyMatrix {
  int vertices;
  int **matrix;

  void insertMatrixFromList(int **m) {
    // Init a 2D matrix VxV and fill with 0
    matrix = new int *[this->vertices];
    for (int i = 0; i < this->vertices; i++) {
      matrix[i] = new int[this->vertices];
      for (int j = 0; j < this->vertices; j++) {
        matrix[i][j] = 0;
      }
    }

    // Convert 0 to 1 for adjacent edges
    for (int i = 0; i < vertices; i++) {
      for (int j = 1; j <= m[i][0]; j++) {
        int index = m[i][j];
        matrix[i][index] = 1;
      }
    }
  }

  void showNumberOfVertex() { std::cout << vertices << std::endl; }

  // Print the metrix to console
  void showAdjacencyList() {
    for (int i = 0; i < this->vertices; i++) {
      for (int j = 0; j < this->vertices; j++) {
        std::cout << this->matrix[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  // Print the metrix to text file with given name
  void printAdjacencyListToFile(std::string fileName) {
    std::ofstream fout(fileName.c_str());
    fout << vertices << std::endl;
    for (int i = 0; i < this->vertices; i++) {
      for (int j = 0; j < this->vertices; j++) {
        fout << this->matrix[i][j] << " ";
      }
      fout << std::endl;
    }
    fout.close();
  }
};

int main() {
  AdjacencyList AL;
  AdjacencyMatrix AM;
  AL.readAdjacencyList("adjacency-list.txt");
  AM.vertices = AL.vertices;
  AM.showNumberOfVertex();
  AM.insertMatrixFromList(AL.matrix);
  AM.showAdjacencyList();
  AM.printAdjacencyListToFile("adjacency-matrix.txt");
  return 0;
}
