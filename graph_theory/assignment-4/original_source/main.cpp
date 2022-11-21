#include <fstream>
#include <iostream>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#define UNVISITED -1
#define INF 999999

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
                const char delim = ' ';
                std::vector<std::string> out;
                std::stringstream ss(line);
                std::string s;
                while (std::getline(ss, s, delim)) {
                    out.push_back(s);
                }
                for (int j = 0; j < out.size(); j++) {
                    gMatrix[row_number][k] = atoi(out[j].c_str());
                    k++;
                }
            }
            file.close();
        }
    }

public:
    AdjacencyMatrix(std::string file_name) {
        load_adjacency_matrix_from_file(file_name);
    }
    bool has_loop() {
        for (int i = 0; i < gNumVertices && gMatrix[i][i] != 0; i++)
            return true;
        return false;
    }

    bool all_visited(std::vector<bool> T) {
        for (int i = 0; i < T.size(); i++)
            if (T[i])
                return false;
        return true;
    }

    void dijkstra(int source) {
        std::vector<bool> T(gNumVertices, true);
        std::vector<int> L(gNumVertices, INF);
        std::vector<int> prev(gNumVertices, UNVISITED);

        // init 0 for source
        L[source] = 0;

        std::string colors[] = {"A", "B", "C", "D", "E",
                                "F", "G", "H", "I", "J"};

        while (!all_visited(T)) {
            int v = get_minimum_T(T, L);
            if (v == UNVISITED)
                break;
            T[v] = false;

            for (int k = 0; k < gNumVertices; k++) {
                if (gMatrix[v][k] > 0) {
                    if (L[k] > L[v] + gMatrix[v][k]) {
                        L[k] = L[v] + gMatrix[v][k];
                        prev[k] = v;
                    }
                }
            }

            std::cout << "T: ";
            for (int i = 0; i < gNumVertices; i++) {
                std::cout << T[i] << " ";
            }
            std::cout << std::endl;
            std::cout << "L: ";
            for (int i = 0; i < gNumVertices; i++) {
                if (L[i] == INF) {
                    std::cout << "I"
                              << " ";
                    continue;
                }
                std::cout << L[i] << " ";
            }
            std::cout << std::endl;
            std::cout << "Prev: ";
            for (int i = 0; i < gNumVertices; i++) {
                if (L[i] == INF) {
                    std::cout << "-"
                              << " ";
                    continue;
                }
                std::cout << colors[prev[i]] << " ";
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < gNumVertices; i++) {
            std::cout << "Duong di ngan nhat tu " << colors[source] << " den "
                      << colors[i] << ": ";
            if (L[i] == INF) {
                std::cout << "Khong co duong di" << std::endl;
                continue;
            }
            std::cout << "Chi phi: " << L[i] << ", Duong di: " << colors[i]
                      << " ";
            if (i == source) {
                std::cout << std::endl;
                continue;
            }
            int p = prev[i];
            while (p != source) {
                std::cout << "<- " << colors[p] << " ";
                p = prev[p];
            }
            std::cout << "<- " << colors[source] << std::endl;
        }
    }

    int get_minimum_T(std::vector<bool> T, std::vector<int> L) {
        int min = -1;
        int length = INF;

        for (int i = 0; i < T.size(); i++) {
            if (T[i]) {
                if (L[i] < length) {
                    min = i;
                    length = L[i];
                }
            }
        }

        return min;
    }

    void bellman(int source) {
        std::vector<std::vector<int> > cost(gNumVertices + 1,
                                            std::vector<int>(gNumVertices));
        std::vector<std::vector<int> > prev(gNumVertices + 1,
                                            std::vector<int>(gNumVertices));
        int step;

        for (int i = 0; i < gNumVertices; i++) {
            cost[0][i] = INF;
            prev[0][i] = UNVISITED;
        }
        cost[0][source] = 0;

        for (step = 1; step <= gNumVertices; step++) {
            for (int k = 0; k < gNumVertices; k++) {
                cost[step][k] = cost[step - 1][k];
                prev[step][k] = prev[step - 1][k];
                for (int v = 0; v < gNumVertices; v++) {
                    if (gMatrix[v][k] != 0 && cost[step - 1][v] != INF) {
                        if (cost[step][k] == INF ||
                            cost[step][k] > cost[step - 1][v] + gMatrix[v][k]) {
                            cost[step][k] = cost[step - 1][v] + gMatrix[v][k];
                            prev[step][k] = v;
                        }
                    }
                }
            }

            int bSame = true;
            for (int k = 0; k < gNumVertices; k++) {
                if (cost[step][k] != cost[step - 1][k]) {
                    bSame = false;
                    break;
                }
            }

            if (bSame)
                break;
        }

        if (step < gNumVertices + 1) {
            for (int i = 0; i < gNumVertices; i++) {
                std::cout << "Duong di ngan nhat tu " << source << " den " << i
                          << ": ";
                if (cost[step][i] == INF) {
                    std::cout << "Khong co duong di" << std::endl;
                    continue;
                }
                std::cout << "Chi phi: " << cost[step][i] << ", Duong di: " << i
                          << " ";
                if (i == source) {
                    std::cout << std::endl;
                    continue;
                }
                int p = prev[step][i];
                while (p != source) {
                    std::cout << "<- " << p << " ";
                    p = prev[step][p];
                }
                std::cout << "<- " << source << std::endl;
            }
        } else {
            std::cout << "Do thi co mach am" << std::endl;
        }
    }
};

int main() {
    AdjacencyMatrix AM("input.txt");

    if (AM.has_loop()) {
        std::cout << "Khong duoc cai dat do thi co canh khuyen." << std::endl;
        return 1;
    }

    int source;
    std::cout << "Tim kiem theo Dijkstra. Vui long nhap source: ";
    std::cin >> source;
    AM.dijkstra(source);

    /* std::cout << "Tim kiem theo Bellman-Ford. Vui long nhap source: "; */
    /* AM.bellman(source); */
    return 0;
};
