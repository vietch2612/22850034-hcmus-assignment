#include <fstream>
#include <iostream>

struct AdjacencyMatrix {
  int vertices;
  int **matrix;

  void readAdjacencyList(std::string fileName) {
    std::ifstream file(fileName);

    if (!file.good()) {
      std::cout << "Input file is not exist!" << std::endl;
      std::exit(1);
    }

    if (file.is_open()) {
      std::string line;
      for (int i = 0; std::getline(file, line); i++) {
        if (i == 0) {
          int n = atoi(line.c_str());
          if (n <= 2) {
            std::cout << "Number of vertices should be greater than 2!"
                      << std::endl;
            exit(1);
          }
          this->vertices = n;
          this->matrix = new int *[this->vertices];
          continue;
        }

        int k = 0;
        int row_number = i - 1;
        int number_of_vertex = line[0] - '0';

        int size = number_of_vertex + 1;
        this->matrix[row_number] = new int[size];

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

struct AdjacencyList {
  int vertices;
  int **matrix;

  void insertListFromMatrix(int **m) {
    // Init a new matrix
    this->matrix = new int *[this->vertices];

    for (int i = 0; i < vertices; i++) {
      int number_of_vertices = 0;
      int k = 1;
      this->matrix[i] = new int[vertices];
      for (int j = 0; j < vertices; j++) {
        if (m[i][j] == 1) {
          matrix[i][k] = j;
          k++;
          number_of_vertices++;
        }
      }
      matrix[i][0] = number_of_vertices;
    }
  }

  void showNumberOfVertex() { std::cout << vertices << std::endl; }

  // Show the metrix
  void showAdjacencyList() {
    for (int i = 0; i < this->vertices; i++) {
      for (int j = 0; j <= this->matrix[i][0]; j++) {
        std::cout << this->matrix[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  void printAdjacencyListToFile(std::string fileName) {
    std::ofstream fout(fileName.c_str());
    fout << vertices << std::endl;
    for (int i = 0; i < this->vertices; i++) {
      for (int j = 0; j <= this->matrix[i][0]; j++) {
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
  AM.readAdjacencyList("adjacency-matrix.txt");
  AL.vertices = AM.vertices;
  AL.showNumberOfVertex();
  AL.insertListFromMatrix(AM.matrix);
  AL.showAdjacencyList();
  AL.printAdjacencyListToFile("adjacency-list.txt");
  return 0;
}
