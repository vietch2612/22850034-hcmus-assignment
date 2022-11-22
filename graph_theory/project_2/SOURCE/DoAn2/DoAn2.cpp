#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#define UNCOLORED -1;

struct Vertices {
    int index;
    int total_degrees;
    int color_index;
};

int get_vertex_color(int index, std::vector<Vertices>& vertices) {
    for (int i = 0; i < vertices.size(); i++)
        if (vertices[i].index == index)
            return vertices[i].color_index;
    return -1;
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
        // Read the matrix from file
        read_adjacency_list_from_file(file_name);
    }

    // Verify that the graph is undirected or directed
    bool is_syncmetric() {
        for (int i = 0; i < gNumVertices; i++)
            for (int j = i; j < gNumVertices; j++)
                if (gMatrix[i][j] != gMatrix[j][i]) {
                    std::cout << i << " " << j << std::endl;
                    return false;
                }

        return true;
    }

    // Verify that the graph has a loop or not
    bool has_loop() {
        for (int i = 0; i < gNumVertices && gMatrix[i][i] != 0; i++)
            return true;
        return false;
    }

    // Verify that the graph has multiple edges or not
    bool has_multiple_edges() {
        for (int i = 0; i < gNumVertices; i++)
            for (int j = 0; j < gNumVertices && gMatrix[i][j] > 1; j++)
                return true;
        return false;
    }

    // Sort the list of vertices by total degrees
    void sort_by_degrees(std::vector<Vertices>& degrees) {
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

    // Return the index of a uncolored vertice with highest degrees
    int
        get_highest_available_degrees_by_vertices(std::vector<Vertices>& degrees) {
        for (int i = 0; i < degrees.size(); i++)
            if (degrees[i].color_index == -1)
                return degrees[i].index;
        return -1;
    }

    // Update the color on the list from given vertice and color index
    void update_color(std::vector<Vertices>& degrees, int v, int color) {
        for (int i = 0; i < degrees.size(); i++)
            if (degrees[i].index == v)
                degrees[i].color_index = color;
    }

    // A list of colors.
    // For printing color name to console
    std::string get_color(int i) {
        std::string colors[] = { "Red", "Green", "Blue", "Yellow"};
        return colors[i];
    }

    void coloring() {
        // A list of vertices with degrees (index, number_of_degress, color)
        std::vector<Vertices> degrees = gDegrees;
        sort_by_degrees(degrees);

        // Init a list of available colors from 0 - > 3
        std::vector<int> colors;
        for (int i = 0; i < 4; i++)
            colors.push_back(i);

        // Total number are used
        int n_colors = 0;

        while (n_colors <= 4) {
            // Get v is index of vertex in the sorted vertices has highest
            // degrees and hasn't been colored
            int u = get_highest_available_degrees_by_vertices(degrees);

            // If u == -1 means all vertices are colored
            // Stop the algorithm
            if (u == -1)
                break;

            // Set color
            update_color(degrees, u, n_colors);

            // Color all not connected vertices with color = n_colors
            for (int j = 0; j < gNumVertices; j++) {
                // Find uncolored and not connected with current u
                if (gMatrix[u][j] == 0 && get_vertex_color(j, degrees) == -1) {
                    // Check if the vertice has connected with other vertices
                    // which has color = current n_colors
                    bool has_connected = true;
                    for (int m = 0; m < gNumVertices; m++) {
                        if (gMatrix[j][m] != 0 &&
                            get_vertex_color(m, degrees) == n_colors) {
                            has_connected = false;
                            break;
                        }
                    }
                    if (has_connected)
                        update_color(degrees, j, n_colors);
                }
            }

            n_colors++;
        }

        std::cout << "So luong mau su dung: " << n_colors << std::endl;
        std::cout << "(Dinh, Mau): ";
        for (int i = 0; i < gNumVertices; i++) {
            std::cout << "(" << degrees[i].index << ","
                << get_color(degrees[i].color_index) << ")";
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