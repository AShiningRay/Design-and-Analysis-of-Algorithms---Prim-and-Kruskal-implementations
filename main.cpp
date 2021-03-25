#include "ADTs/Prim.hpp"
#include "ADTs/Kruskal.hpp"
#include <cmath>
#include <fstream>
#include <string.h>

float EuclideanDistance(float x1, float y1, float x2, float y2);
void showResultingClasses(int *classes_kruskal, int numlines, int opt);

int main()
{
    std::ifstream data_file;
    std::ifstream classes_file;
    std::string readline;

    int numlines = 0;

    data_file.open("./Files/dados.txt", std::ios::in);
    while(getline(data_file, readline) )
    {
        numlines++;
    }
    data_file.close();

    float pointxyval[numlines][2]; //[x][y]
    int classes_kruskal[numlines];
    int vertex[numlines];
    int i=0;
    char *piece_data;

    data_file.open("./Files/dados.txt", std::ios::in);

    while(getline(data_file, readline) )
    {
        vertex[i] = i;
        piece_data = strtok(&readline[0], "	");
        pointxyval[i][0] = atof(piece_data);
        piece_data = strtok(NULL, "	");
        pointxyval[i][1] = atof(piece_data);
        i++;
    }

    data_file.close();
    i=0;
    classes_file.open("./Files/classes.txt", std::ios::in);

    while(getline(classes_file, readline) )
    {
        classes_kruskal[i] = atoi(&readline[0]);
        i++;
    }


    int vertexnum = numlines, edgenum = (((numlines * numlines) - numlines)/2);

    Graph_Kruskal graph_kruskal(vertexnum, edgenum);
    Graph_Prim graph_prim(vertexnum);

    showResultingClasses(classes_kruskal, numlines, 0);

    for (i=0; i<numlines; i++){
        for (int j=i+1; j<numlines; j++){
            graph_kruskal.addEdgeAndWeight(vertex[i], vertex[j], EuclideanDistance(pointxyval[i][0], pointxyval[i][1], pointxyval[j][0], pointxyval[j][1]));
            graph_prim.put_edge(vertex[i], vertex[j], (EuclideanDistance(pointxyval[i][0], pointxyval[i][1], pointxyval[j][0], pointxyval[j][1])));
        }
    }

    std::cout << "\n--------------- KRUSKAL MST ---------------\n" << std::endl;
    graph_kruskal.kruskalAlgorithm(classes_kruskal);
    std::cout << std::endl;
    std::cout << "\n--------------- PRIM MST ---------------\n" << std::endl;
    graph_prim.calculate_Prim();
    std::cout << std::endl;

    showResultingClasses(classes_kruskal, numlines, 1);
    return 0;
}

float EuclideanDistance(float x1, float y1, float x2, float y2)
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

void showResultingClasses(int *classes_kruskal, int numlines, int opt)
{
    int j=0;
    (opt == 1)  ? std::cout << "\n--------------- CLASS VALUE AFTER EXECUTING THE KRUSKAL ALGORITHM ---------------\n" << std::endl
                : std::cout << "\n--------------- CLASS VALUE BEFORE EXECUTING THE KRUSKAL ALGORITHM ---------------\n" << std::endl;

        while(j < numlines)
        {
            std::cout <<"Class Value - Kruskal: "<< classes_kruskal[j] <<std::endl;
            j++;
        }
}
