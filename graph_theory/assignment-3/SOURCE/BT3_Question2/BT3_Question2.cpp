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


std::vector<Edge> init_list_edges(AdjacencyMatrix AM) {
    std::vector<std::vector<int> > g = AM.gMatrix;
    int m = AM.gNumVertices;
    std::vector<Edge> edges;
    int count = 0;

    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (g[i][j] != 0) {
                Edge edge;
                edge.w = i;
                edge.v = j;
                edge.weight = g[i][j];
                edges.push_back(edge);
            }
        }
    }

    return edges;
}

void print_edge(Edge e) {
    std::cout << e.w << " - " << e.v << ": " << e.weight << std::endl;
}

void sort_edges(std::vector<Edge>& edges) {
    for (int i = 0; i < edges.size(); i++) {
        for (int j = 0; j < edges.size(); j++) {
            if (edges[i].weight <= edges[j].weight) {
                // In case a pair of vertices have a same weight
                if (edges[i].weight == edges[j].weight && edges[i].w > edges[j].w)
                    continue;
                Edge tmp;
                tmp = edges[i];
                edges[i] = edges[j];
                edges[j] = tmp;
            }
        }
    }
}


void kruskal(AdjacencyMatrix AM) {
    std::vector<Edge> edges;
    edges = init_list_edges(AM);

    sort_edges(edges);

    std::vector<std::vector<int> > g = AM.gMatrix;
    int m = AM.gNumVertices;
    int n = m - 1;
    Edge* T = new Edge[n];
    int nT = 0;

    int* label = new int[m];
    for (int i = 0; i < m; i++)
        label[i] = i;

    int total_weight = 0;
    for (int k = 0; k < edges.size(); k++) {
        Edge e = edges[k];
        if (label[e.w] != label[e.v]) {
            total_weight += e.weight;
            T[nT++] = e;

            int old_id = label[e.w];
            int new_id = label[e.v];

            for (int i = 0; i < m; i++) {
                if (label[i] == old_id)
                    label[i] = new_id;
            }
        }
    }

    std::cout << "Tap canh cua cay khung:" << std::endl;

    for (int i = 0; i < n; i++) {
        std::cout << T[i].w << " - " << T[i].v << ": " << T[i].weight
            << std::endl;
    }
    std::cout << "Trong so cua cay khung: " << total_weight << std::endl;
}

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

    kruskal(AM);

    return 0;
};