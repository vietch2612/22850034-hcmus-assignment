#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#define UNCOLORED -1

struct Vertices {
    int index;
    int total_degrees;
    int color_index;
};

int get_vertex_color(int index, std::vector<Vertices> &vertices) {
    for (int i = 0; i < vertices.size(); i++)
        if (vertices[i].index == index)
            return vertices[i].color_index;
    return UNCOLORED;
};

class AdjacencyMatrix {
    int gNumVertices;
    std::vector<std::vector<int> > gMatrix;
    std::vector<Vertices> gDegrees;

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
                for (int j = 0; j < line.length(); j++) {
                    if (line[j] != ' ') {
                        if (j == 0) {
                            Vertices v;
                            v.index = i - 1;
                            v.total_degrees = line[j] - '0';
                            v.color_index = UNCOLORED;
                            gDegrees.push_back(v);
                            continue;
                        }
                        int length = line[j] - '0';
                        gMatrix[i - 1][length] = 1;
                    }
                }
            }
            file.close();
        }
    }

public:
    AdjacencyMatrix(std::string file_name) {
        read_adjacency_list_from_file(file_name);
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

    bool has_multiple_edges() {
        for (int i = 0; i < gNumVertices; i++)
            for (int j = 0; j < gNumVertices && gMatrix[i][j] > 1; j++)
                return true;
        return false;
    }

    void sort_by_degrees(std::vector<Vertices> &degrees) {
        for (int i = 0; i < gNumVertices; i++) {
            for (int j = 0; j < gNumVertices; j++) {
                if (degrees[i].total_degrees >= degrees[j].total_degrees) {
                    // In case a pair of vertices have a same total degrees
                    if (degrees[i].total_degrees == degrees[j].total_degrees &&
                        degrees[i].index > degrees[j].index)
                        continue;
                    Vertices tmp;
                    tmp = degrees[i];
                    degrees[i] = degrees[j];
                    degrees[j] = tmp;
                }
            }
        }
    }

    std::string get_color_name(int i) {
        std::string colors[] = {"Red",  "Green", "Blue",  "Yellow",
                                "Cyan", "Black", "White", "Purple"};
        return colors[i];
    }

    void coloring() {
        std::vector<Vertices> degrees = gDegrees;
        sort_by_degrees(degrees);

        std::vector<int> colors;
        for (int i = 0; i < 5; i++)
            colors.push_back(i);
        int n_colors = 0;

        for (int i = 0; i < gNumVertices; i++) {
            if (degrees[i].color_index == UNCOLORED) {
                for (int j = 0; j < colors.size(); j++) {
                    for (int k = 0; k < gNumVertices; k++)
                        if (gMatrix[degrees[i].index][k] != 0)
                            if (get_vertex_color(k, degrees) == j)
                                goto next_color;
                    degrees[i].color_index = j;
                    if (j > n_colors)
                        n_colors = j;
                    goto next_vertice;
                next_color:;
                }
            }
        next_vertice:;
        }

        std::cout << "So luong mau su dung: " << n_colors + 1 << std::endl;
        std::cout << "(Dinh, Mau): ";
        for (int i = 0; i < gNumVertices; i++) {
            std::cout << "(" << degrees[i].index << ","
                      << get_color_name(degrees[i].color_index) << ")";
            if (i < gNumVertices - 1)
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }
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

    if (AM.has_multiple_edges()) {
        std::cout << "Khong duoc cai dat do thi co canh boi." << std::endl;
        return 1;
    }

    AM.coloring();

    return 0;
};
