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
                }

                if (i == 1) {
                    gStart = line[0] - '0';
                    gEnd = line[2] - '0';
                    continue;
                }

                int k = 0;
                int row_number = i - 2;

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

    // bool is_syncmetric() {
    //     for (int i = 0; i < gVertices; i++)
    //         for (int j = i + 1; j < gVertices; j++)
    //             if (gMatrix[i][j] != gMatrix[j][i])
    //                 return false;
    //     return true;
    // }

    bool is_syncmetric() {
        for (int i = 0; i < gVertices; i++)
            for (int j = i; j < gVertices; j++)
                if (gMatrix[i][j] != gMatrix[j][i])
                    std::cout << "BNOT" << std::endl;
        return true;
    }

    bool dfs(int v, std::vector<bool> &visited, std::vector<int> &path) {
        std::cout << v << " ";
        visited[v] = true;
        path.push_back(v);

        if (v == gEnd)
            return true;

        for (int i = 0; i < gVertices; i++) {
            if (gMatrix[v][i]) {
                if (visited[i]) {
                    continue;
                }
                if (dfs(i, visited, path))
                    return true;
                else
                    path.pop_back();
            }
        }

        return false;
    }

    bool bfs(int v, std::vector<bool> &visited, std::vector<int> &path) {
        std::cout << v << " ";
        visited[v] = true;
        path.push_back(v);

        if (v == gEnd)
            return true;

        for (int i = 0; i < gVertices; i++) {
            if (gMatrix[v][i]) {
                if (visited[i]) {
                    continue;
                }
                if (dfs(i, visited, path))
                    return true;
                else
                    path.pop_back();
            }
        }

        return false;
    }

    void find_connected_by_dfs(int v, std::vector<bool> &visited) {
        visited[v] = true;
        std::cout << v << " ";

        for (int i = 0; i < gVertices; i++) {
            if (gMatrix[v][i]) {
                if (!visited[i])
                    find_connected_by_dfs(i, visited);
            }
        }
    }

public:
    AdjacencyMatrix(std::string file_name) {
        load_adjacency_matrix_from_file(file_name);
        gIsSyncmetric = is_syncmetric();
    }

    int get_vertices() { return gVertices; }
    bool is_undirected() { return gIsSyncmetric; }

    void find_path_by_dfs() {
        std::vector<bool> visited(gVertices, false);
        std::vector<int> path;

        std::cout << "Danh sach cac dinh duyet theo thu tu:" << std::endl;
        if (dfs(gStart, visited, path)) {
            std::cout << "\nDuong di theo kieu xuoi:" << std::endl;
            for (int i = 0; i < path.size(); i++) {
                std::cout << path[i];
                if (i != path.size() - 1)
                    std::cout << " -> ";
            }
            std::cout << std::endl;
        } else {
            std::cout << std::endl;
            std::cout << "Khong tim thay duong" << std::endl;
        }
    }

    void find_connected_components() {
        std::vector<bool> visited(gVertices, false);
        for (int i = 0; i < gVertices; i++) {
            if (!visited[i]) {
                find_connected_by_dfs(i, visited);
                std::cout << std::endl;
            }
        }
    }
};

int main() {
    AdjacencyMatrix AM("input.txt");
    AM.find_path_by_dfs();
    if (AM.is_undirected())
        AM.find_connected_components();

    return 0;
}