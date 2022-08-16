#include <iostream>
#include <fstream>

class AdjacencyList
{
    public:

    int vertex;
    int** matrix;

    // Read the list
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
                // update vertex if this is the first line
                if (i == 0)
                {
                    int v_number = atoi(line.c_str());
                    if (v_number <= 2)
                    {
                        std::cout << "Vertex should be greater than 2" << std::endl;
                        exit(1);
                    }
                    vertex = v_number;
                    // init a new matrix
                    matrix = new int*[vertex];
                    continue;
                }

                // put value in the row i -1
                int k = 0;
                int row_number = i - 1;
                int number_of_vertex = line[0] - '0';
                int size = number_of_vertex + 1;
                matrix[row_number] = new int[size];

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
        std::cout << vertex << std::endl;
    }

    // Show the metrix
    void showAdjacencyList()
    {
        for (int i = 0; i < vertex; i ++)
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
        bool is_2d_graph = true;
        
        for (int i = 0; i < vertex; i ++)
        {
            for (int j = 1; j < matrix[i][0]; j ++)
            {
                for (int k = 1; k < matrix[j][0]; k++)
                {
                    std::cout << i << "," << j << "," << k << std::endl;
                    if (matrix[j][k] == i)
                    {
                        std::cout << "broke" << std::endl;
                        continue;
                    }
                    
                }
                is_2d_graph = false;
            }
            
        }

        if (is_2d_graph)
        {
            std::cout << "Danh sach ke bieu dien do thi hai chieu" << std::endl;
        }
        else
        {
            std::cout << "Danh sach ke bieu dien do thi mot chieu" << std::endl;
        }

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
