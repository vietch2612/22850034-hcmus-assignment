#include <iostream>
#include <fstream>

class AdjacencyMatrix
{
    public:

    int vertex;
    int** matrix;

    // Read the Matrix
    void readAdjacencyMatrix(std::string fileName)
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
                    for (int i = 0; i < vertex; i++)
                        matrix[i] = new int[vertex];
                    continue;
                }

                // put value in the row i -1
                int k = 0;
                int row_number = i - 1;
                for (int j = 0; j < line.length(); j++)
                {
                    if (line[j] != ' ')
                    {
                        matrix[row_number][k] = line[j];
                        k++;
                    }
                }
            }
            file.close();
        }
    }

    // Show the vertex
    void showVertex()
    {
        std::cout << vertex << std::endl;
    }

    // Show the metrix
    void showAdjacencyMatrix()
    {
        for (int i = 0; i < vertex; i ++)
        {
            for (int j = 0; j < vertex; j ++)
            {
                std::cout << (char) matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }

    }

    // Verify the Adjacency Matrix
    void verifyAdjacencyMatrix()
    {
        bool is_symmetric = true;
        for (int i = 0; i < vertex; i ++)
        {
            for (int j = 0; j < vertex; j ++)
            {
                if (matrix[i][j] != matrix[j][i]) 
                {
                    is_symmetric = false;
                    break;
                }
            }

        }

        is_symmetric ? std::cout << "Ma tran doi xung" << std::endl : std::cout << "Ma tran khong doi xung" << std::endl;
    }
};

int main ()
{
    AdjacencyMatrix AM;
    AM.readAdjacencyMatrix("adjacency-matrix.txt");
    AM.showVertex();
    AM.showAdjacencyMatrix();
    AM.verifyAdjacencyMatrix();
    return 0;
}
