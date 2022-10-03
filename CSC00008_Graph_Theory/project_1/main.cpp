#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <vector>

class AdjacencyMatrix {
    int gNumVertices;
    int **gMatrix;
    int gStart;
    int gEnd;
    int gIsSyncmetric;

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
                if (i == 0) {
                    int n = atoi(line.c_str());
                    if (n <= 2) {
                        std::cout
                            << "Number of vertices should be greater than 2!"
                            << std::endl;
                        exit(1);
                    }
                    gNumVertices = n;
                    gMatrix = new int *[gNumVertices];
                }

                if (i == 1) {
                    /* gStart = line[0] - '0'; */
                    /* gEnd = line[2] - '0'; */
                    std::string delimiter = " ";
                    continue;
                }

                int k = 0;
                int row_number = i - 2;

                gMatrix[row_number] = new int[gNumVertices];

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

    bool dfs(int start, int end, std::vector<bool> &visited,
             std::vector<int> &steps, std::vector<int> &path) {
        visited[start] = true;
        steps.push_back(start);
        path.push_back(start);

        if (start == end && end >= 0)
            return true;

        for (int i = 0; i < gNumVertices; i++) {
            if (gMatrix[start][i]) {
                if (visited[i]) {
                    continue;
                }
                if (dfs(i, end, visited, steps, path))
                    return true;
                else
                    path.pop_back();
            }
        }

        return false;
    }

    bool dfs2(int start, int end, std::vector<bool> &visited,
              std::vector<int> &steps, std::vector<int> &path,
              std::vector<std::vector<int> > g) {
        visited[start] = true;
        steps.push_back(start);
        path.push_back(start);

        if (start == end && end >= 0)
            return true;

        for (int i = 0; i < gNumVertices; i++) {
            if (g[start][i]) {
                if (visited[i]) {
                    continue;
                }
                if (dfs(i, end, visited, steps, path))
                    return true;
                else
                    path.pop_back();
            }
        }

        return false;
    }

    bool is_strong() {
        std::cout << "Checking if this graph is strongly connected!"
                  << std::endl;
        for (int i = 0; i < gNumVertices; i++)
            for (int j = 0; j < gNumVertices; j++) {
                std::vector<bool> visited(gNumVertices, false);
                std::vector<int> steps;
                std::vector<int> path;
                if (!dfs(i, j, visited, steps, path)) {
                    std::cout << "Can not find from " << i << " to " << j
                              << " -> Not strongly connected" << std::endl;
                    return false;
                }
            }
        return true;
    }

    bool is_weak(std::vector<std::vector<int> > g) {
        std::cout << "Checking if this graph is weekly connected!" << std::endl;
        for (int i = 0; i < gNumVertices; i++)
            for (int j = 0; j < gNumVertices; j++) {
                std::vector<bool> visited(gNumVertices, false);
                std::vector<int> steps;
                std::vector<int> path;
                if (!dfs2(i, j, visited, steps, path, g)) {
                    std::cout << "Can not find from " << i << " to " << j
                              << std::endl;
                    return false;
                }
            }
        return true;
    }

    std::vector<std::vector<int> > convert() {
        std::vector<int> row(gNumVertices, 0);
        std::vector<std::vector<int> > new_g(gNumVertices, row);

        for (int i = 0; i < gNumVertices; i++) {
            for (int j = 0; j < gNumVertices; j++) {
                if (gMatrix[i][j] == 1 || gMatrix[j][i] == 1) {
                    new_g[i][j] = 1;
                    new_g[j][i] = 1;
                }
            }
        }

        return new_g;
    }

public:
    AdjacencyMatrix(std::string file_name) {
        load_adjacency_matrix_from_file(file_name);
    }

    void declare_type_of_graph() {
        if (is_strong())
            std::cout << "Strong" << std::endl;
        else if (is_weak(convert()))
            std::cout << "Week" << std::endl;
        else
            std::cout << "TBD" << std::endl;
    }
};

int main() {
    AdjacencyMatrix AM("input.txt");

    AM.declare_type_of_graph();
    return 0;
}
