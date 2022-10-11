#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

class AdjacencyMatrix {
    int gNumVertices;
    int** gMatrix;
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
                    gMatrix = new int* [gNumVertices];
                }

                if (i == 1) {
                    int space = line.find(" ");
                    gStart = atoi(line.substr(0, space).c_str());
                    gEnd = atoi(line.substr(space).c_str());
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

    bool is_syncmetric() {
        for (int i = 0; i < gNumVertices; i++)
            for (int j = i; j < gNumVertices; j++)
                if (gMatrix[i][j] != gMatrix[j][i])
                    return false;
        return true;
    }

    bool dfs(int start, int end, std::vector<bool>& visited,
        std::vector<int>& steps, std::vector<int>& path) {
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

    void bfs(int start, int end, std::vector<int>& previous,
        std::vector<int>& steps, std::vector<bool>& visited) {
        std::queue<int> my_queue;

        my_queue.push(start);

        while (!my_queue.empty()) {
            int u = my_queue.front();
            my_queue.pop();

            if (visited[u])
                continue;

            visited[u] = true;
            steps.push_back(u);

            if (u == end && end >= 0)
                return;

            for (int i = 0; i < gNumVertices; i++) {
                if (gMatrix[u][i] != 0 && !visited[i]) {
                    my_queue.push(i);
                    if (previous[i] == -1)
                        previous[i] = u;
                }
            }
        }
    }

    std::vector<int> backtrace(int start, int end, std::vector<int>& previous) {
        std::vector<int> path;
        for (int v = end; v != -1; v = previous[v])
            path.push_back(v);
        return path;
    }

public:
    AdjacencyMatrix(std::string file_name) {
        load_adjacency_matrix_from_file(file_name);
        gIsSyncmetric = is_syncmetric();
    }

    int get_vertices() { return gNumVertices; }
    bool is_undirected() { return gIsSyncmetric; }

    bool has_loop() {
        for (int i = 0; i < gNumVertices && gMatrix[i][i] != 0; i++)
            return true;
        return false;
    }

    bool has_multiple_edges() {
        for (int i = 0; i < gNumVertices; i++)
            for (int j = 0; j < gNumVertices && gMatrix[i][j] > 1; j++)
                return true;
        return false;
    }

    void find_path_by_dfs() {
        std::vector<bool> visited(gNumVertices, false);
        std::vector<int> steps;
        std::vector<int> path;
        bool is_found = false;

        if (dfs(gStart, gEnd, visited, steps, path))
            is_found = true;

        std::cout << "Danh sach cac dinh duyet theo thu tu:" << std::endl;
        for (int i = 0; i < steps.size(); i++)
            std::cout << steps[i] << " ";
        std::cout << std::endl;

        if (is_found) {
            std::cout << "Duong di theo kieu xuoi:" << std::endl;
            for (int i = 0; i < steps.size(); i++) {
                std::cout << steps[i];
                if (i != steps.size() - 1)
                    std::cout << " -> ";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Khong tim thay duong" << std::endl;
        }
    }

    void find_path_by_bfs() {
        std::vector<int> steps;
        std::vector<int> previous(gNumVertices, -1);
        std::vector<bool> visited(gNumVertices, false);

        bfs(gStart, gEnd, previous, steps, visited);

        std::cout << "Danh sach cac dinh da duyet theo thu tu:" << std::endl;
        for (int i = 0; i < steps.size(); i++)
            std::cout << steps[i] << " ";
        std::cout << std::endl;

        std::vector<int> path;
        path = backtrace(gStart, gEnd, previous);
        if (path.back() == gStart) {
            std::cout << "Duong di theo kieu nguoc:" << std::endl;
            for (int i = 0; i < path.size(); i++) {
                std::cout << path[i];
                if (i < path.size() - 1)
                    std::cout << " <- ";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Khong tim thay duong" << std::endl;
        }
    }

    void find_connected_by_dfs() {
        std::vector<std::vector<int> > cp; // connected components
        std::vector<bool> visited(gNumVertices, false);

        for (int i = 0; i < gNumVertices; i++) {
            if (!visited[i]) {
                std::vector<int> steps;
                std::vector<int> path;
                dfs(i, -1, visited, steps, path);
                cp.push_back(steps);
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
        std::vector<bool> visited(gNumVertices, false);

        for (int i = 0; i < gNumVertices; i++) {
            if (!visited[i]) {
                std::vector<int> steps;
                std::vector<int> path;
                std::vector<int> previous(gNumVertices, -1);

                bfs(i, -1, previous, steps, visited);
                cp.push_back(steps);
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

    AM.find_path_by_bfs();
    if (AM.is_undirected())
        AM.find_connected_by_bfs();

    return 0;
}