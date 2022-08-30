#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <vector>

class AdjacencyMatrix {
    int gVertices;
    int **gMatrix;

    void load_adjacency_matrix_from_file(std::string file_name) {
        std::ifstream file(file_name);

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
                    // Exit early if the number of vertices isn't met the
                    // requirement
                    if (n <= 2) {
                        std::cout
                            << "Number of vertices should be greater than 2!"
                            << std::endl;
                        exit(1);
                    }
                    gVertices = n;
                    gMatrix = new int *[gVertices];
                    continue;
                }

                int k = 0;
                int row_number = i - 1;

                gMatrix[row_number] = new int[gVertices];

                // Loop through the string characters
                // If the character != space -> convert to int then push to the
                // array
                for (int j = 0; j < line.length(); j++) {
                    if (line[j] != ' ') {
                        gMatrix[row_number][k] = line[j] - '0';
                        k++;
                    }
                }
            }
            file.close();
        }
    }

    bool is_complete_graph() {
        for (int i = 0; i < gVertices; i++)
            for (int j = 0; j < gVertices; j++)
                if ((i != j && gMatrix[i][j] != 1) ||
                    ((i == j) && gMatrix[i][j] != 0))
                    return false;

        return true;
    }

    std::vector<int> count_degrees() {
        std::vector<int> degrees;

        for (int i = 0; i < gVertices; i++) {
            int count = 0;
            for (int j = 0; j < gVertices; j++) {
                if (gMatrix[i][j] != 0)
                    count += gMatrix[i][j];
                if (i == j)
                    count += gMatrix[i][j];
            }
            degrees.push_back(count);
        }

        return degrees;
    }

    bool dfs(int vertex, std::set<int> &visited, int parent) {
        visited.insert(vertex);

        for (int v = 0; v < gVertices; v++) {
            std::cout << "v: " << v << std::endl;
            if (gMatrix[vertex][v]) {
                if (v == parent)
                    continue;
                if (visited.find(v) != visited.end())
                    return true;
                if (dfs(v, visited, vertex))
                    return true;
            }
        }
        return false;
    }

    bool has_cycle() {
        std::vector<int> degrees = count_degrees();
        for (int i = 0; i < degrees.size() && degrees[i] != 2; i++)
            return false;

        std::set<int> visited;
        for (int v = 0; v < gVertices; v++) {
            std::cout << "v: " << v << std::endl;
            if (visited.find(v) != visited.end())
                continue;
            if (dfs(v, visited, -1))
                return true;
        }
        return false;
    }

public:
    AdjacencyMatrix(std::string file_name) {
        load_adjacency_matrix_from_file(file_name);
    }

    void print_number_of_vertices() { std::cout << gVertices << std::endl; }

    void print_adjacency_matrix_to_console() {
        for (int i = 0; i < gVertices; i++) {
            for (int j = 0; j < gVertices; j++)
                std::cout << gMatrix[i][j] << " ";
            std::cout << std::endl;
        }
    }

    void print_is_complete_graph() {
        is_complete_graph()
            ? std::cout << "Day la do thi day du K" << gVertices << std::endl
            : std::cout << "Day khong phai ma tran day du" << std::endl;
    }

    void print_is_regular_graph() {
        bool result = true;
        std::vector<int> degrees = count_degrees();
        for (int i = 0; i < degrees.size() - 1; i++) {
            if (degrees[i] != degrees[i + 1]) {
                result = false;
                break;
            }
        }
        result ? std::cout << "Day la do thi " << degrees[0] << "-chinh quy"
                           << std::endl
               : std::cout << "Day khong phai la do thi chinh quy" << std::endl;
    }

    void print_is_cycle_graph() {
        has_cycle() ? std::cout << "1" << std::endl
                    : std::cout << "0" << std::endl;
    }
};

int main() {
    AdjacencyMatrix AM("input.txt");

    AM.print_number_of_vertices();
    AM.print_adjacency_matrix_to_console();
    AM.print_is_complete_graph();
    AM.print_is_regular_graph();
    AM.print_is_cycle_graph();

    std::cout << "-------------------------" << std::endl;

    AdjacencyMatrix AM2("input2.txt");

    AM2.print_number_of_vertices();
    AM2.print_adjacency_matrix_to_console();
    AM2.print_is_complete_graph();
    AM2.print_is_regular_graph();
    AM2.print_is_cycle_graph();

    return 0;
}
