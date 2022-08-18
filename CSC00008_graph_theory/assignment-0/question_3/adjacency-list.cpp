#include <iostream>
#include <fstream>

class AdjacencyList
{
    public:

    int vertices;
    int **matrix;

    void readAdjacencyList(std::string fileName)
    {
        std::ifstream file(fileName);

        if (!file.good())
        {
            std::cout << "Input file is not exist!" << std::endl;
            std::exit(1);
        }

        if (file.is_open())
        {
            std::string line;
            for (int i = 0; std::getline(file, line); i++)
            {
                // Get the number of vertices in the first line
                if (i == 0)
                {
                    int n = atoi(line.c_str());
                    if (n <= 2)
                    {
                        std::cout << "Number of vertices should be greater than 2!" << std::endl;
                        exit(1);
                    }
                    vertices = n;
                    // Initialize a new row of the matrix
                    matrix = new int*[vertices];
                    continue;
                }

                // Insert value into the matrix by row number = i-1
                // Because the first row is number of vertices
                int k = 0;
                int row_number = i - 1;
                int number_of_vertex = line[0] - '0';
                // Initialize the size of each row
                // Each row contains the number of adjacent edges of the vertex
                // So that means we have to increase the size by 1
                int size = number_of_vertex + 1;
                matrix[row_number] = new int[size];
                
                // Loop through the string characters
                // If the character != space -> convert to int then push to the array
                for (int j = 0; j < line.length(); j++)
                {
                    if (line[j] != ' ')
                    {
                        matrix[row_number][k] = line[j] - '0';
                        k++;
                    }
                }
            }
            file.close();
        }
    }

    // Show the vertex
    void showNumberOfVertex()
    {
        std::cout << vertices << std::endl;
    }

    // Show the metrix
    void showAdjacencyList()
    {
        for (int i = 0; i < vertices; i ++)
        {
            for (int j = 0; j <= matrix[i][0]; j ++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }

    }

    // Verify the Adjacency List
    int verifyAdjacencyList()
    {
        // Assume the given matrix is 2d graph
        // Then verify that
        bool is_2d_graph = true;
        for (int i = 0; i < vertices; i ++)
        {   
            for (int j = 1; j <= matrix[i][0]; j++)
            {
                for (int k = 1; k <= matrix[j][0]; k++)
                {
                    // ==> 0 [2,->1,2] First round, we found the connection from v(0) -> v(1)
                    //     1 [2,0,3]
                    //     2 [2,0,3]
                    //     3 [2,1,2]
                    // So we need to verify that there's a connection from v(1) -> v(0)
                    //     0 [2,1,2]
                    // ==> 1 [2,->0,3]
                    //     2 [2,0,3]
                    //     3 [2,1,2]
                    int vertex_to_compare = matrix[i][j];
                    if (matrix[vertex_to_compare][k] == i)
                    {
                        // Found the connection
                        // Exit the loop and verify the next J
                        goto exit_loop;
                    }
                }
            }
            // Connection not found.
            // Update the assumption then exit the loop
            is_2d_graph = false;
            break;
            exit_loop:;
        }

        std::string result = is_2d_graph ?
             "Danh sach ke bieu dien do thi hai chieu" : "Danh sach ke bieu dien do thi mot chieu";
        std::cout << result << std::endl;
        return 0;
    }
};

int main ()
{
    AdjacencyList AL;
    AL.readAdjacencyList("adjacency-list.txt");
    AL.showNumberOfVertex();
    AL.showAdjacencyList();
    AL.verifyAdjacencyList();
    return 0;
}
