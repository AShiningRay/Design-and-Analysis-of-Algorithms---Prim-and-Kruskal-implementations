#include "ADTs/Prim.hpp"
#include "ADTs/Kruskal.hpp"
#include <cmath>
#include <fstream>
#include <string.h>

float EuclideanDistance(float x1, float y1, float x2, float y2);
int getNumberSets(int *classes);
void write_results_file(int *classes);

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
    int vertex[numlines];
    int i=0;
    char *piece_data;
    int classes[numlines];

    data_file.open("./Files/dados.txt", std::ios::in);

    while(getline(data_file, readline) )
    {
        classes[i] = i;
        vertex[i] = i;
        piece_data = strtok(&readline[0], "	");
        pointxyval[i][0] = atof(piece_data);
        piece_data = strtok(NULL, "	");
        pointxyval[i][1] = atof(piece_data);
        i++;
    }
    int k;

    std::cout << "Please type the k value: " << std::endl;
    std::cin >> k;

    data_file.close();

    int vertexnum = numlines, edgenum = (((numlines * numlines) - numlines)/2);

    Graph_Kruskal graph_kruskal(vertexnum, edgenum);
    Graph_Prim graph_prim(vertexnum);

    for (i=0; i<numlines; i++){
        for (int j=i+1; j<numlines; j++){
            graph_kruskal.addEdgeAndWeight(vertex[i], vertex[j], EuclideanDistance(pointxyval[i][0], pointxyval[i][1], pointxyval[j][0], pointxyval[j][1]));
            graph_prim.put_edge(vertex[i], vertex[j], (EuclideanDistance(pointxyval[i][0], pointxyval[i][1], pointxyval[j][0], pointxyval[j][1])));
        }
    }

    std::cout << "\n--------------- KRUSKAL MST ---------------\n" << std::endl;
    graph_kruskal.kruskalAlgorithm(classes, k);
    std::cout << std::endl;
    std::cout << "\n--------------- PRIM MST ---------------\n" << std::endl;
    //graph_prim.calculate_Prim();
    std::cout << std::endl;

    write_results_file(classes);

    return 0;
}

float EuclideanDistance(float x1, float y1, float x2, float y2)
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

void write_results_file(int *classes)
{
  std::ofstream myfile ("./Files/results.txt");
  if (myfile.is_open())
  {
    for (int i=0; i<788; i++){
    myfile << classes[i];
    if (i < 787)
        myfile << "\n";
    }
    myfile.close();
  }
  else std::cout << "Unable to open file";
}


