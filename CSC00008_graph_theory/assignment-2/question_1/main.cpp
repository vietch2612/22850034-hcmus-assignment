#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <queue>
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
                if (i == 0) {
                    int n = atoi(line.c_str());
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

    bool is_syncmetric() {
        for (int i = 0; i < gVertices; i++)
            for (int j = i; j < gVertices; j++)
                if (gMatrix[i][j] != gMatrix[j][i])
                    return false;
        return true;
    }

    bool dfs(int u, int v, std::vector<bool> &visited, std::vector<int> &path,
             std::vector<int> &route) {
        visited[u] = true;
        path.push_back(u);
        route.push_back(u);

        if (u == v && v >= 0)
            return true;

        for (int i = 0; i < gVertices; i++) {
            if (gMatrix[u][i]) {
                if (visited[i]) {
                    continue;
                }
                if (dfs(i, v, visited, path, route))
                    return true;
                else
                    route.pop_back();
            }
        }

        return false;
    }

    void bfs(int start, std::vector<int> &previous, std::vector<int> &path,
             std::vector<bool> &visited) {
        std::queue<int> my_queue;

        my_queue.push(start);

        while (!my_queue.empty()) {
            int u = my_queue.front();
            my_queue.pop();

            if (visited[u])
                continue;

            visited[u] = true;
            path.push_back(u);

            for (int i = 0; i < gVertices; i++) {
                if ((gMatrix[u][i] != 0) && (!visited[i])) {
                    my_queue.push(i);
                    if (previous[i] == -1)
                        previous[i] = u;
                }
            }
        }
    }

    std::vector<int> backtrace(int start, int end, std::vector<int> &previous) {
        std::vector<int> route;
        for (int v = end; v != -1; v = previous[v])
            route.push_back(v);
        return route;
    }

public:
    AdjacencyMatrix(std::string file_name) {
        load_adjacency_matrix_from_file(file_name);
        gIsSyncmetric = is_syncmetric();
    }

    int get_vertices() { return gVertices; }
    bool is_undirected() { return gIsSyncmetric; }

    bool has_loop() {
        for (int i = 0; (i < gVertices) && (gMatrix[i][i] != 0); i++)
            return true;
        return false;
    }

    bool has_multiple_edges() {
        for (int i = 0; i < gVertices; i++)
            for (int j = 0; j < gVertices; j++)
                if (gMatrix[i][j] > 1)
                    return true;
        return false;
    }

    void find_path_by_dfs() {
        std::vector<bool> visited(gVertices, false);
        std::vector<int> path;
        std::vector<int> route;
        bool is_found = false;

        if (dfs(gStart, gEnd, visited, path, route))
            is_found = true;

        std::cout << "Danh sach cac dinh duyet theo thu tu:" << std::endl;
        for (int i = 0; i < path.size(); i++)
            std::cout << path[i] << " ";

        if (is_found) {
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

    void find_path_by_bfs() {
        std::vector<int> path;
        std::vector<int> route;
        std::vector<int> previous(gVertices, -1);
        std::vector<bool> visited(gVertices, false);

        bfs(gStart, previous, path, visited);

        std::cout << "Danh sach cac dinh da vieng tham:" << std::endl;
        for (int i = 0; i < path.size(); i++)
            std::cout << path[i] << " ";
        std::cout << std::endl;

        std::cout << "Duong di theo kieu nguoc:" << std::endl;
        route = backtrace(gStart, gEnd, previous);
        for (int i = 0; i < route.size(); i++) {
            std::cout << route[i];
            if (i < route.size() - 1)
                std::cout << " <- ";
        }
        std::cout << std::endl;
    }

    void find_connected_by_dfs() {
        std::vector<std::vector<int> > cp;
        std::vector<bool> visited(gVertices, false);

        for (int i = 0; i < gVertices; i++) {
            if (!visited[i]) {
                std::vector<int> path;
                std::vector<int> route;
                dfs(i, -1, visited, path, route);
                cp.push_back(path);
            }
        }

        std::cout << "So thanh phan lien thong: " << cp.size() << std::endl;
        for (int i = 0; i < cp.size(); i++) {
            std::cout << "Thanh phan lien thong thu: " << i + 1 << ": ";
            for (int j = 0; j < cp[i].size(); j++)
                std::cout << cp[i][j] << " ";
            std::cout << std::endl;
        }
    }

    void find_connected_by_bfs() {
        std::vector<std::vector<int> > cp;
        std::vector<bool> visited(gVertices, false);

        for (int i = 0; i < gVertices; i++) {
            if (!visited[i]) {
                std::vector<int> path;
                std::vector<int> route;
                std::vector<int> previous(gVertices, -1);

                bfs(i, previous, path, visited);
                cp.push_back(path);
            }
        }

        std::cout << "So thanh phan lien thong: " << cp.size() << std::endl;
        for (int i = 0; i < cp.size(); i++) {
            std::cout << "Thanh phan lien thong thu: " << i + 1 << ": ";
            for (int j = 0; j < cp[i].size(); j++)
                std::cout << cp[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

int main() {
    AdjacencyMatrix AM("input.txt");

    if (AM.has_loop()) {
        std::cout << "Khong duoc cai dat do thi co canh khuyen." << std::endl;
        return 1;
    }

    if (AM.has_multiple_edges()) {
        std::cout << "Khong duoc cai dat do thi co canh boi." << std::endl;
        return 1;
    }

    AM.find_path_by_dfs();
    if (AM.is_undirected())
        AM.find_connected_by_dfs();

    AM.find_path_by_bfs();
    if (AM.is_undirected())
        AM.find_connected_by_bfs();
    return 0;
}
