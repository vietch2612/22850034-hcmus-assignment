#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

class AdjacencyMatrix {
    int gVertices;
    int **gMatrix;
    bool gIsSymmetric;

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

    bool is_undirected() {
        for (int i = 0; i < gVertices; i++)
            for (int j = 0; j < gVertices; j++)
                if (gMatrix[i][j] != gMatrix[j][i])
                    return false;
        return true;
    }

    int count_number_of_edges() {
        int canh_do_thi = 0;

        for (int i = 0; i < gVertices; i++) {
            if (gIsSymmetric) {
                for (int j = 0 + i; j < gVertices; j++)
                    canh_do_thi += gMatrix[i][j];
            } else {
                for (int j = 0; j < gVertices; j++) {
                    if (gMatrix[i][j] > 0)
                        canh_do_thi += gMatrix[i][j];
                }
            }
        }

        return canh_do_thi;
    }

    int count_multiple_edges() {
        int count = 0;
        for (int i = 0; i < gVertices; i++) {
            if (gIsSymmetric) {
                for (int j = 0 + i; j < gVertices; j++) {
                    if (gMatrix[i][j] > 1)
                        count++;
                }
            } else {
                for (int j = 0; j < gVertices; j++) {
                    if (gMatrix[i][j] > 1) {
                        count++;
                    }
                }
            }
        }

        return count;
    }

    int count_loops() {
        int count = 0;
        for (int i = 0; i < gVertices; i++) {
            for (int j = 0; j < gVertices; j++) {
                if ((gMatrix[i][j] != 0) && (i == j))
                    count++;
            }
        }

        return count;
    }

    int **count_bac_directed() {
        int **counts = 0;
        counts = new int *[gVertices];

        for (int i = 0; i < gVertices; i++) {
            counts[i] = new int[2];

            for (int j = 0; j < gVertices; j++) {
                if (gMatrix[j][i] > 0)
                    counts[i][0] += gMatrix[j][i];
                if (gMatrix[i][j] > 0)
                    counts[i][1] += gMatrix[i][j];
            }
        }

        return counts;
    }

    std::vector<int> count_bac_undirected() {
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

    int count_edges_by_condition(int so_dinh) {
        int count = 0;

        if (gIsSymmetric) {
            std::vector<int> degrees = count_bac_undirected();
            for (int i = 0; i < degrees.size(); i++) {
                if (degrees[i] == so_dinh)
                    count++;
            }
        } else {
            int **degrees = count_bac_directed();
            for (int i = 0; (i < gVertices); i++) {
                if (degrees[i][0] + degrees[i][1] == so_dinh)
                    count++;
            }
        }

        return count;
    }

    int count_hang_edges() { return count_edges_by_condition(1); }
    int count_isolated_edges() { return count_edges_by_condition(0); }

public:
    AdjacencyMatrix(std::string file_name) {
        load_adjacency_matrix_from_file(file_name);
        gIsSymmetric = is_undirected();
    }

    void print_vertices() { std::cout << gVertices << std::endl; }

    void print_number_of_vertices() {
        std::cout << "So dinh cua do thi: " << gVertices << std::endl;
    }

    void print_adjacency_matrix_to_console() {
        for (int i = 0; i < gVertices; i++) {
            for (int j = 0; j < gVertices; j++)
                std::cout << gMatrix[i][j] << " ";
            std::cout << std::endl;
        }
    }

    void print_adjacency() {
        gIsSymmetric ? std::cout << "Do thi vo huong" << std::endl
                     : std::cout << "Do thi co huong" << std::endl;
    }

    void print_number_of_edges() {
        std::cout << "So canh cua do thi: " << count_number_of_edges()
                  << std::endl;
    }

    void print_number_of_multiple_edges() {
        std::cout << "So cap dinh xuat hien canh boi: "
                  << count_multiple_edges() << std::endl;
    }

    void print_number_of_loops() {
        std::cout << "So canh khuyen: " << count_loops() << std::endl;
    }

    void print_graph_type() {
        bool has_multiple_edge = count_multiple_edges() > 0;
        bool has_loop = count_loops() > 0;
        std::string graph_type = "unknown";

        if (gIsSymmetric) {
            if (has_multiple_edge)
                // Co canh boi
                if (has_loop)
                    graph_type = "Gia do thi";
                else
                    graph_type = "Da do thi";
            else
                graph_type = "Don do thi";
        } else {
            if (has_loop) {
                if (has_multiple_edge)
                    graph_type = "Da do thi co huong";
                else
                    graph_type = "Do thi co huong";
            }
        }
        std::cout << graph_type << std::endl;
    }

    void print_degrees() {
        if (gIsSymmetric) {
            std::vector<int> degrees = count_bac_undirected();
            std::cout << "Bac cua tung dinh:" << std::endl;
            for (int i = 0; i < gVertices; i++)
                std::cout << i << "(" << degrees[i] << ") ";
            std::cout << std::endl;
        } else {
            int **degrees = count_bac_directed();
            std::cout << "Bac cua tung dinh:" << std::endl;
            for (int i = 0; i < gVertices; i++)
                std::cout << i << "(" << degrees[i][0] << "-" << degrees[i][1]
                          << ") ";
            std::cout << std::endl;
        }
    }

    void print_so_dinh_treo() {
        std::cout << "So dinh treo: " << count_hang_edges() << std::endl;
    }

    void print_number_isolated_edges() {
        std::cout << "So dinh co lap: " << count_isolated_edges() << std::endl;
    }
};

int main() {
    AdjacencyMatrix AM("input.txt");

    AM.print_vertices();
    AM.print_adjacency_matrix_to_console();
    AM.print_adjacency();
    AM.print_number_of_vertices();
    AM.print_number_of_edges();
    AM.print_number_of_multiple_edges();
    AM.print_number_of_loops();
    AM.print_so_dinh_treo();
    AM.print_number_isolated_edges();
    AM.print_degrees();
    AM.print_graph_type();

    return 0;
}
