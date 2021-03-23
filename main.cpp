#include "ADTs/Prim.hpp"
#include "ADTs/Kruskal.hpp"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string.h>

float EuclideanDistance(float x1, float y1, float x2, float y2);

int main()
{
    std::ifstream data_file;
    std::ifstream classes_file;
    std::string readline;

    int numlines = 0;

    data_file.open("./Files/dados.txt", ios::in);
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


    data_file.open("./Files/dados.txt", ios::in);

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

    classes_file.open("./Files/classes.txt", ios::in);

    while(getline(classes_file, readline) )
    {
        classes_kruskal[i] = atoi(&readline[0]);
        classes_prim[i] = classes_kruskal[i];
        i++;
    }
    int j=0;

    while(j < 788)
    {
        printf("Classes: %d\n", classes_kruskal[j]);
        j++;
    }

    int vertexnum = numlines, edgenum = (((numlines * numlines) - numlines)/2);

    Graph graph(vertexnum, edgenum);


    for (i=0; i<numlines; i++){
        for (int j=i+1; j<numlines; j++){
            graph.addEdgeAndWeight(vertex[i], vertex[j], EuclideanDistance(pointxyval[i][0], pointxyval[i][1], pointxyval[j][0], pointxyval[j][1]));
        }
    }


    graph.kruskalAlgorithm(classes_kruskal);
    j = 0;
    while(j < 788)
    {
        printf("Classes: %d\n", classes_kruskal[j]);
        j++;
    }
    return 0;
}

float EuclideanDistance(float x1, float y1, float x2, float y2)
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}
