#include "ADTs/Prim.hpp"
#include "ADTs/Kruskal.hpp"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string.h>

float EucledeanDistance(float x1, float y1, float x2, float y2);

int main()
{
    std::ifstream data_file;
    std::ifstream classes_file;
    data_file.open("./Files/dados.txt", ios::in);
    classes_file.open("./Files/classes.txt", ios::in);

    std::string readline;

    float pointxyval[788][2]; //[x][y]
    float classes[788];
    int i=0;
    char *piece_data;
    while(!data_file.eof()){
        getline(data_file, readline);
        piece_data = strtok(&readline[0], "	");
        pointxyval[i][0] = atof(piece_data);
        piece_data = strtok(NULL, "	");
        pointxyval[i][1] = atof(piece_data);
        i++;
    }

    float aux = pointxyval[0][0];
    i=0;
    while(!classes_file.eof()){
        getline(classes_file, readline);
        classes[i] = atoi(&readline[0]);
        i++;
    }
     pointxyval[0][0] = aux;

    for (i=0; i<787; i++){
        printf("distancia do ponto (%.2f, %.2f) ate o ponto (%.2f, %.2f) e: %.2f\n",pointxyval[i][0], pointxyval[i][1], pointxyval[i+1][0], pointxyval[i+1][1], EucledeanDistance(pointxyval[i][0], pointxyval[i][1], pointxyval[i+1][0], pointxyval[i+1][1]));
    }
    i = 0;

    while(i<788){
        std::cout<<"Valor classes: "<<classes[i]<<std::endl;
        i++;
    }
}

float EucledeanDistance(float x1, float y1, float x2, float y2){
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}
