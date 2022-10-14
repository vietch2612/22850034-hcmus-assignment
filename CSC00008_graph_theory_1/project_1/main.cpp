#include <fstream>
#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <vector>

#define UNVISITED -1

class AdjacencyMatrix {
    int gNumVertices;
    std::vector<std::vector<int> > gMatrix;

    void read_adjacency_list_from_file(std::string fileName) {
        std::ifstream file(fileName);

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

                // Insert value into the matrix by row number = i-1
                // Because the first row is number of vertices
                // If the character != space -> convert to int then push to the
                // array
                for (int j = 2; j < line.length(); j++) {
                    if (line[j] != ' ') {
                        int length = line[j] - '0';
                        gMatrix[i - 1][length] = 1;
                    }
                }
            }
            file.close();
        }
    }

    bool dfs(int start, int end, std::vector<bool> &visited,
             std::vector<int> &path, std::vector<std::vector<int> > g) {
        visited[start] = true;
        path.push_back(start);

        if (start == end && end >= 0)
            return true;

        for (int i = 0; i < gNumVertices; i++) {
            if (g[start][i]) {
                if (visited[i]) {
                    continue;
                }
                if (dfs(i, end, visited, path, g))
                    return true;
                else
                    path.pop_back();
            }
        }
        return false;
    }

    int count_number_of_strong_connected(std::vector<std::vector<int> > g) {
        int count = 0;
        for (int i = 0; i < gNumVertices; i++) {
            std::vector<bool> visited(gNumVertices, false);
            std::vector<int> path;
            dfs(i, -1, visited, path, g);

            for (int j = 0; j < visited.size(); j++)
                if (visited[j] == false)
                    goto cnt;
            count++;
        cnt:;
        }
        return count;
    }

    bool is_weak(std::vector<std::vector<int> > g) {
        g = convert_to_undirected(g);
        for (int i = 0; i < gNumVertices; i++)
            for (int j = 0; j < gNumVertices; j++) {
                std::vector<bool> visited(gNumVertices, false);
                std::vector<int> path;
                if (!dfs(i, j, visited, path, g)) {
                    return false;
                }
            }
        return true;
    }

    std::vector<std::vector<int> >
    convert_to_undirected(std::vector<std::vector<int> > g) {
        std::vector<int> row(gNumVertices, 0);
        std::vector<std::vector<int> > new_g(gNumVertices, row);

        for (int i = 0; i < gNumVertices; i++) {
            for (int j = 0; j < gNumVertices; j++) {
                if (g[i][j] == 1 || g[j][i] == 1) {
                    new_g[i][j] = 1;
                    new_g[j][i] = 1;
                }
            }
        }
        return new_g;
    }

    void dfs_find(int u, int ids[], int root[], std::stack<int> &stack,
                  bool on_stack[], std::vector<std::vector<int> > &cps) {
        stack.push(u);
        on_stack[u] = true;
        static int id = 0;
        ids[u] = root[u] = id++;

        for (int v = 0; v < gNumVertices; v++) {
            if (gMatrix[u][v]) {
                if (ids[v] == UNVISITED) {
                    dfs_find(v, ids, root, stack, on_stack, cps);
                    root[u] = minimum(root[u], root[v]);
                } else if (on_stack[v]) {
                    root[u] = minimum(root[u], ids[v]);
                }
            }
        }

        if (root[u] == ids[u]) {
            std::vector<int> cp;
            while (stack.top() != u) {
                int popped_item = stack.top();
                cp.push_back(popped_item);
                on_stack[popped_item] = false;
                stack.pop();
            }

            int popped_item = stack.top();
            on_stack[popped_item] = false;
            stack.pop();

            cp.push_back(popped_item);
            cps.push_back(cp);
        }
    }

    int minimum(int x, int y) {
        if (x < y)
            return x;
        return y;
    };

public:
    AdjacencyMatrix(std::string file_name) {
        read_adjacency_list_from_file(file_name);
    }

    void print_type_of_graph() {
        int count = count_number_of_strong_connected(gMatrix);
        if (count == gNumVertices) {
            std::cout << "Do thi lien thong manh." << std::endl;
            return;
        }
        if (count > 0) {
            std::cout << "Do thi lien thong tung phan" << std::endl;
            return;
        }
        if (is_weak(gMatrix)) {
            std::cout << "Do thi lien thong yeu" << std::endl;
            return;
        }
        std::cout << "Do thi khong lien thong" << std::endl;
    }

    void print_connected_components() {
        int ids[gNumVertices];
        int root[gNumVertices];
        bool on_stack[gNumVertices];
        std::stack<int> stack;
        std::vector<std::vector<int> > cps;

        for (int i = 0; i < gNumVertices; i++) {
            ids[i] = UNVISITED;
            root[i] = UNVISITED;
            on_stack[i] = false;
        }

        // Find connected components and store it into 2d vector: cps
        for (int i = 0; i < gNumVertices; i++)
            if (ids[i] == UNVISITED)
                dfs_find(i, ids, root, stack, on_stack, cps);

        // Print the connected components: cps to console
        for (int i = 0; i < cps.size(); i++) {
            std::cout << "Thanh phan lien thong manh " << i + 1 << ": ";
            for (int j = 0; j < cps[i].size(); j++) {
                std::cout << cps[i][j];
                if (j < cps[i].size() - 1)
                    std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }

    bool is_syncmetric() {
        for (int i = 0; i < gNumVertices; i++)
            for (int j = i; j < gNumVertices; j++)
                if (gMatrix[i][j] != gMatrix[j][i])
                    return false;
        return true;
    }

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
};

int main() {
    AdjacencyMatrix AM("input.txt");

    if (AM.is_syncmetric()) {
        std::cout << "Khong duoc cai dat do thi vo huong." << std::endl;
        return 1;
    }

    if (AM.has_loop()) {
        std::cout << "Khong duoc cai dat do thi co canh khuyen." << std::endl;
        return 1;
    }

    if (AM.has_multiple_edges()) {
        std::cout << "Khong duoc cai dat do thi co canh boi." << std::endl;
        return 1;
    }

    AM.print_type_of_graph();
    AM.print_connected_components();
    return 0;
}
