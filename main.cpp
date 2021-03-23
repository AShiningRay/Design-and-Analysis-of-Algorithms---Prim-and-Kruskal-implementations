#include "ADTs/Prim.hpp"
#include "ADTs/Kruskal.hpp"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string.h>

float EuclideanDistance(float x1, float y1, float x2, float y2);
void show_results_classes(int *classes_kruskal, int *classes_prim, int numlines, int opt);

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
    int classes_kruskal[numlines], classes_prim[numlines];
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
        classes_prim[i] = classes_kruskal[i];
        i++;
    }

    int vertexnum = numlines, edgenum = (((numlines * numlines) - numlines)/2);

    Graph graph_kruskal(vertexnum, edgenum);
    Graph_Prim graph_prim(vertexnum);

    show_results_classes(classes_kruskal, classes_prim, numlines, 0);

    for (i=0; i<numlines; i++){
        for (int j=i+1; j<numlines; j++){
            graph_kruskal.addEdgeAndWeight(vertex[i], vertex[j], EuclideanDistance(pointxyval[i][0], pointxyval[i][1], pointxyval[j][0], pointxyval[j][1]));
            graph_prim.put_edge(vertex[i], vertex[j], (1000*EuclideanDistance(pointxyval[i][0], pointxyval[i][1], pointxyval[j][0], pointxyval[j][1])));
        }
    }
    graph_kruskal.kruskalAlgorithm(classes_kruskal);
    graph_prim.calculates_Prim(classes_prim);

    show_results_classes(classes_kruskal, classes_prim, numlines, 1);
    return 0;
}

float EuclideanDistance(float x1, float y1, float x2, float y2)
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

void show_results_classes(int *classes_kruskal, int *classes_prim, int numlines, int opt)
{
    int j=0;
    (opt == 1)  ? std::cout << "\n--------------- CLASS VALUE AFTER EXECUTING THE PRIM AND KRUSKAL ALGORITHM ---------------\n" << std::endl
                : std::cout << "\n--------------- CLASS VALUE BEFORE EXECUTING THE PRIM AND KRUSKAL ALGORITHM ---------------\n" << std::endl;

        while(j < numlines)
        {
            std::cout <<"Class Value - Kruskal: "<< classes_kruskal[j] <<std::endl;
            j++;
        }
        j=0;

        std::cout << "\n-------------------------------\n" << std::endl;

        while(j < numlines)
        {
            std::cout <<"Class Value - Prim: "<< classes_prim[j] <<std::endl;
            j++;
        }
}
