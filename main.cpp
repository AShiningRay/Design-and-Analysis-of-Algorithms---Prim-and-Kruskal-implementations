#include "ADTs/Prim.hpp"
#include "ADTs/Kruskal.hpp"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

float EuclideanDistance(float x1, float y1, float x2, float y2);

int main()
{
    std::ifstream data_file;
    std::ifstream classes_file;
    std::string readline;

    unsigned int numlines = 0;

    data_file.open("./Files/dados.txt", ios::in);
    while(getline(data_file, readline) )
    {
        numlines++;
    }

    data_file.close();

    float pointxyval[numlines][2]; //[x][y]

    float classes[numlines];
    int i=0;
    char *piece_data;


    data_file.open("./Files/dados.txt", ios::in);

    while(getline(data_file, readline) )
    {
        //getline(data_file, readline);
        piece_data = strtok(&readline[0], "	");
        pointxyval[i][0] = atof(piece_data);
        piece_data = strtok(NULL, "	");
        pointxyval[i][1] = atof(piece_data);
        i++;
    }
    data_file.close();

    //float aux = pointxyval[0][0];
    i=0;

    readline = "\0";
    classes_file.open("./Files/classes.txt", ios::in);

    while(getline(classes_file, readline) )
    {
        classes[i] = atoi(&readline[0]);
        i++;
    }
    //pointxyval[0][0] = aux;

    for (i=0; i<numlines-1; i++)
        std::cout << "distance from (" << pointxyval[i][0] << ", " << pointxyval[i][1] << ") to (" << pointxyval[i+1][0] << ", " << pointxyval[i+1][1] << "): " << EuclideanDistance(pointxyval[i][0], pointxyval[i][1], pointxyval[i+1][0], pointxyval[i+1][1]) << std::endl;

    i = 0;

    while(i < numlines)
    {
        std::cout << "Class value: " << classes[i] << std::endl;
        i++;
    }
}

float EuclideanDistance(float x1, float y1, float x2, float y2)
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}
