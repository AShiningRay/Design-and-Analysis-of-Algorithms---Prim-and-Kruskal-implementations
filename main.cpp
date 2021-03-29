#include "ADTs/Prim.hpp"
#include "ADTs/Kruskal.hpp"
#include <cmath>
#include <string.h>

//Prototypes
float EuclideanDistance(float x1, float y1, float x2, float y2);
void write_results_file(int *classes);

int main()
{
    //Variables used to read the data file.
    std::ifstream data_file;
    std::ifstream classes_file;
    std::string readline;

    int numlines = 0;

    data_file.open("./Files/dados.txt", std::ios::in);

    //Function used to calculate the amount of lines.
    while(getline(data_file, readline) )
    {
        numlines++;
    }
    data_file.close();

    //Matrix used to storage the vertices.
    float pointxyval[numlines][2]; //[x][y]

    //Array used to storage the amount of vertices.
    int vertex[numlines];
    int i=0;

    //Pointer used to assist the read data.
    char *piece_data;

    //Array to storage the groups.
    int classes_kruskal[numlines];
    int classes_prim[numlines];

    data_file.open("./Files/dados.txt", std::ios::in);

    //Function to read the file line by line.
    while(getline(data_file, readline) )
    {
        vertex[i] = i; //Fills the array with integers from 0 to 787.
        piece_data = strtok(&readline[0], "	");
        pointxyval[i][0] = atof(piece_data);
        piece_data = strtok(NULL, "	");
        pointxyval[i][1] = atof(piece_data);
        i++;
    }

    //Gets the k value from user.
    int k;
    std::cout << "Please type the k value: " << std::endl;
    std::cin >> k;

    data_file.close();

    //Creates the graph for kruskal and Prim algorithm.
    int vertexnum = numlines, edgenum = (((numlines * numlines) - numlines)/2);

    Graph_Kruskal graph_kruskal(vertexnum, edgenum);
    Graph_Prim graph_prim(vertexnum);

    //This function will put the vertices and the edges in the graphs with a complexity O((N^2 - N)/2).
    for (i=0; i<numlines; i++){
        for (int j=i+1; j<numlines; j++){
            graph_kruskal.addEdgeAndWeight(vertex[i], vertex[j], EuclideanDistance(pointxyval[i][0], pointxyval[i][1], pointxyval[j][0], pointxyval[j][1]));
            graph_prim.put_edge(vertex[i], vertex[j], (EuclideanDistance(pointxyval[i][0], pointxyval[i][1], pointxyval[j][0], pointxyval[j][1])));
        }
    }

    //Calculates the results and shows the MSTs.
    std::cout << "\n--------------- KRUSKAL MST ---------------\n" << std::endl;
    graph_kruskal.kruskalAlgorithm(classes_kruskal, k);
    std::cout << std::endl;
    std::cout << "\n--------------- PRIM MST ---------------\n" << std::endl;
    graph_prim.calculate_Prim(k, classes_prim);
    std::cout << std::endl;

    return 0;
}

//Calculates the Euclidean Distance.
float EuclideanDistance(float x1, float y1, float x2, float y2)
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}



