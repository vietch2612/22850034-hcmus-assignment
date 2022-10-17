#include <fstream>
#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <vector>

struct AdjacencyMatrix {
    int gNumVertices;
    std::vector<std::vector<int> > gMatrix;

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
                    for (int j = 0; j < gNumVertices; j++) {
                        std::vector<int> row(gNumVertices, 0);
                        gMatrix.push_back(row);
                    }
                    continue;
                }

                int k = 0;
                int row_number = i - 1;

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

public:
    AdjacencyMatrix(std::string file_name) {
        load_adjacency_matrix_from_file(file_name);
    }

    bool is_syncmetric() {
        for (int i = 0; i < gNumVertices; i++)
            for (int j = i; j < gNumVertices; j++)
                if (gMatrix[i][j] != gMatrix[j][i]) {
                    std::cout << i << " " << j << std::endl;
                    return false;
                }
        return true;
    }

    bool has_loop() {
        for (int i = 0; i < gNumVertices && gMatrix[i][i] != 0; i++)
            return true;
        return false;
    }
};

struct Edge {
    int v;
    int w;
    int weight;

    Edge() {};
};

void prim(AdjacencyMatrix AM, int source) {
    std::vector<std::vector<int> > g = AM.gMatrix;
    int m = AM.gNumVertices;
    int n = m - 1;
    Edge* T = new Edge[n];
    bool* marked = new bool[m];
    int nT = 0;
    int total_weight = 0;

    for (int i = 0; i < m; ++i)
        marked[i] = false;
    marked[source] = true;

    while (nT < n) {
        Edge edgeMin;
        int minimum = 999999999;

        for (int w = 0; w < m; w++) {
            if (marked[w]) {
                for (int v = 0; v < m; v++) {
                    if (!marked[v] && g[w][v]) {
                        if (g[w][v] < minimum) {
                            edgeMin.w = w;
                            edgeMin.v = v;
                            minimum = g[w][v];
                            edgeMin.weight = minimum;
                        }
                    }
                }
            }
        }
        T[nT++] = edgeMin;
        marked[edgeMin.v] = true;
        total_weight += minimum;
    }

    std::cout << "Tap canh cua cay khung:" << std::endl;
    for (int i = 0; i < n; i++) {
        Edge edge = T[i];
        std::cout << edge.w << " - " << edge.v << ": " << edge.weight
            << std::endl;
    }
    std::cout << "Trong so cua cay khung: " << total_weight << std::endl;
};


int main() {
    AdjacencyMatrix AM("input.txt");

    if (!AM.is_syncmetric()) {
        std::cout << "Khong duoc cai dat do thi co huong." << std::endl;
        return 1;
    }

    if (AM.has_loop()) {
        std::cout << "Khong duoc cai dat do thi co canh khuyen." << std::endl;
        return 1;
    }

    prim(AM, 0);

    return 0;
};