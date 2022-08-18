#include <fstream>
#include <iostream>

class AdjacencyList {
  int gVertices;
  int **gMatrix;

public:
  void read_adjacency_list_from_file(std::string fileName) {
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
          this->gVertices = n;
          // Initialize rows of the matrix
          this->gMatrix = new int *[this->gVertices];
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
        this->gMatrix[row_number] = new int[size];

        // Loop through the string characters
        // If the character != space -> convert to int then push to the array
        for (int j = 0; j < line.length(); j++) {
          if (line[j] != ' ') {
            this->gMatrix[row_number][k] = line[j] - '0';
            k++;
          }
        }
      }
      file.close();
    }
  }

  int get_vertices() { return gVertices; };

  int **get_adjacency_matrix() {
    int **tmp_matrix;
    // Init a 2D matrix VxV and fill all with 0
    tmp_matrix = new int *[this->gVertices];
    for (int i = 0; i < this->gVertices; i++) {
      tmp_matrix[i] = new int[this->gVertices];
      for (int j = 0; j < this->gVertices; j++) {
        tmp_matrix[i][j] = 0;
      }
    }

    // Convert 0 to 1 for adjacent edges
    for (int i = 0; i < gVertices; i++) {
      for (int j = 1; j <= gMatrix[i][0]; j++) {
        int index = gMatrix[i][j];
        tmp_matrix[i][index] = 1;
      }
    }

    return tmp_matrix;
  }
};

struct AdjacencyMatrix {
  int vertices;
  int **matrix;

  AdjacencyMatrix(int v, int **m) {
    this->vertices = v;
    this->matrix = m;
  }

  void print_number_of_vertices() { std::cout << vertices << std::endl; }

  // Print the metrix to console
  void print_adjacency_matrix_to_console() {
    for (int i = 0; i < this->vertices; i++) {
      for (int j = 0; j < this->vertices; j++) {
        std::cout << this->matrix[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  // Print the metrix to text file with given name
  void print_adjacency_matrix_to_file(std::string fileName) {
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
  AL.read_adjacency_list_from_file("adjacency-list.txt");

  AdjacencyMatrix AM(AL.get_vertices(), AL.get_adjacency_matrix());
  AM.print_number_of_vertices();
  AM.print_adjacency_matrix_to_console();
  AM.print_adjacency_matrix_to_file("adjacency-matrix.txt");

  return 0;
}
