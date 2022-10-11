#include <fstream>
#include <iostream>
#include <string>

struct AdjacencyMatrix {
  int gVertices;
  int **matrix;

  // Read the Matrix
  void read_adjacency_matrix_from_file(std::string fileName) {
    std::ifstream file(fileName);

    if (!file.good()) {
      std::cout << "Input file is not exist!" << std::endl;
      std::exit(1);
    }

    if (file.is_open()) {
      std::string line;
      for (int i = 0; std::getline(file, line); i++) {
        // update gVertices if this is the first line
        if (i == 0) {
          int v_number = atoi(line.c_str());
          if (v_number <= 2) {
            std::cout << "Number of vertices should be greater than 2" << std::endl;
            exit(1);
          }
          gVertices = v_number;
          // init a new matrix
          matrix = new int *[gVertices];
          for (int i = 0; i < gVertices; i++)
            matrix[i] = new int[gVertices];
          continue;
        }

        // put value in the row i -1
        int k = 0;
        int row_number = i - 1;
        for (int j = 0; j < line.length(); j++) {
          if (line[j] != ' ') {
            matrix[row_number][k] = line[j];
            k++;
          }
        }
      }
      file.close();
    }
  }

  // Show the gVertices
  void print_number_of_vertices() { std::cout << gVertices << std::endl; }

  // Show the metrix
  void print_adjacency_matrix() {
    for (int i = 0; i < gVertices; i++) {
      for (int j = 0; j < gVertices; j++) {
        std::cout << (char)matrix[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  // Verify the Adjacency Matrix
  void verify_matrix_symmetric() {
    bool is_symmetric = true;
    for (int i = 0; i < gVertices; i++) {
      for (int j = 0; j < gVertices; j++) {
        if (matrix[i][j] != matrix[j][i]) {
          is_symmetric = false;
          break;
        }
      }
    }

    is_symmetric ? std::cout << "Ma tran doi xung" << std::endl
                 : std::cout << "Ma tran khong doi xung" << std::endl;
  }
};

int main() {
  AdjacencyMatrix AM;
  AM.read_adjacency_matrix_from_file("adjacency-matrix.txt");
  AM.print_number_of_vertices();
  AM.print_adjacency_matrix();
  AM.verify_matrix_symmetric();
  return 0;
}
