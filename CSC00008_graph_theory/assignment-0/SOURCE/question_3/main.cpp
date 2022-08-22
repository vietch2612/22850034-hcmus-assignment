// Question 3
#include <fstream>
#include <iostream>
#include <string>

struct AdjacencyMatrix {
  int vertices;
  int **matrix;

  void read_adjacency_matrix_from_file(std::string fileName) {
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
          vertices = n;
          // Initialize rows of the matrix
          matrix = new int *[vertices];
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
        matrix[row_number] = new int[size];

        // Loop through the string characters
        // If the character != space -> convert to int then push to the array
        for (int j = 0; j < line.length(); j++) {
          if (line[j] != ' ') {
            matrix[row_number][k] = line[j] - '0';
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

  void convert_matrix_to_list(int **m) {
    // Init a new matrix
    matrix = new int *[vertices];

    /**
     * The idea is that we just loop over the matrix and if the value is 1
     * We insert the index of j into the new matrix at [i][k+1]
     * k+1 because k = 0 is the position of the number of vertices
     * [0,->1,1,0] [i=0][j=1]
     * [1,0,0,1]
     * [1,0,0,1]
     * [0,1,1,0]
     * -> Insert J into the new matrix at the end of [0][0+1]
     * [-,1]
     * [-]
     * [-]
     * [-]
     */
    for (int i = 0; i < vertices; i++) {
      int number_of_vertices = 0;
      int k = 1;
      matrix[i] = new int[vertices];
      for (int j = 0; j < vertices; j++) {
        if (m[i][j] == 1) {
          matrix[i][k] = j;
          // Increase the index
          k++;
          // Update the number of vertices
          number_of_vertices++;
        }
      }
      // Update number of vertices in the position 0 on each row
      matrix[i][0] = number_of_vertices;
    }
  }

  void print_number_of_vertices() { std::cout << vertices << std::endl; }

  // Show the metrix
  void print_adjacency_list_to_console() {
    for (int i = 0; i < vertices; i++) {
      for (int j = 0; j <= matrix[i][0]; j++) {
        std::cout << matrix[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  void print_adjacency_list(std::string fileName) {
    std::ofstream fout(fileName.c_str());
    fout << vertices << std::endl;
    for (int i = 0; i < vertices; i++) {
      for (int j = 0; j <= matrix[i][0]; j++) {
        fout << matrix[i][j] << " ";
      }
      fout << std::endl;
    }
    fout.close();
  }
};

int main() {
  AdjacencyMatrix AM;
  AM.read_adjacency_matrix_from_file("adjacency-matrix.txt");

  AdjacencyList AL;
  AL.vertices = AM.vertices;
  AL.print_number_of_vertices();
  AL.convert_matrix_to_list(AM.matrix);
  AL.print_adjacency_list_to_console();
  AL.print_adjacency_list("adjacency-list.txt");
  return 0;
}
