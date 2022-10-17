// Prim's Algorithm in C++

#include <cstring>
#include <iostream>
using namespace std;

#define INF 9999999

// number of vertices in grapj
#define V 9

// create a 2d array of size 5x5
// for adjacency matrix to represent graph

int G[V][V] = {
    {0, 7, 6, 10, 15, 0, 0, 0, 0},  {7, 0, 13, 8, 0, 12, 0, 0, 0},
    {6, 13, 0, 0, 9, 0, 0, 1, 0},   {10, 8, 0, 0, 19, 16, 17, 0, 0},
    {15, 0, 9, 19, 0, 0, 11, 5, 0}, {0, 12, 0, 16, 0, 0, 14, 0, 18},
    {0, 0, 0, 17, 11, 14, 0, 3, 2}, {0, 0, 1, 0, 5, 0, 3, 0, 4},
    {0, 0, 0, 0, 0, 18, 2, 4, 0},
};

string get_char(int i) {
    std::string d[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};
    return d[i];
}

int main() {
    int no_edge; // number of edge

    // create a array to track selected vertex
    // selected will become true otherwise false
    int selected[V];

    // set selected false initially
    memset(selected, false, sizeof(selected));

    // set number of edge to 0
    no_edge = 0;

    // the number of egde in minimum spanning tree will be
    // always less than (V -1), where V is number of vertices in
    // graph

    // choose 0th vertex and make it true
    selected[0] = true;

    int x; //  row number
    int y; //  col number

    // print for edge and weight
    cout << "Edge"
         << " : "
         << "Weight";
    cout << endl;

    int total_weight = 0;
    while (no_edge < V - 1) {
        // For every vertex in the set S, find the all adjacent vertices
        //  , calculate the distance from the vertex selected at step 1.
        //  if the vertex is already in the set S, discard it otherwise
        // choose another vertex nearest to selected vertex  at step 1.

        int min = INF;
        x = 0;
        y = 0;

        for (int i = 0; i < V; i++) {
            if (selected[i]) {
                // std::cout << "working with vertice: " << get_char(i) <<
                // std::endl;
                // for (int k = 0; k < V; k++)
                //     if (selected[k])
                //         cout << get_char(k) << ",";
                // cout << endl;
                for (int j = 0; j < V; j++) {

                    if (!selected[j] &&
                        G[i][j]) { // not in selected and there is an edge
                        // std::cout << "(" << get_char(i) << "," << get_char(j)
                        //           << "),";
                        // for (int k = 0; k < V; k++)
                        //     if (selected[k])
                        //         cout << get_char(k) << ",";
                        // cout << endl;
                // cout << "----" << endl;

                        if (min > G[i][j]) {
                            
                            min = G[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
                // cout << "------------" << std::endl;
            }
        }
        total_weight += min;
        cout << get_char(x) << " - " << get_char(y) << " :  " << G[x][y]
             << " Total: " << total_weight;
        cout << endl;

        selected[y] = true;
        no_edge++;
    }

    return 0;
}