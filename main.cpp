#include "ADTs/Prim.hpp"
#include "ADTs/Kruskal.hpp"

#include <iostream>
#include <fstream>

int main()
{
    fstream data_file, classes_file;
    data_file.open("./Files/dados.txt", ios::in);
    classes_file.open("./Files/classes.txt", ios::in);


    if (!data_file)
		std::cout << "There is no such data file or directory!" << std::endl;

	else
		std::cout << "Data file has been opened successfully!" << std::endl;

    if (!classes_file)
		std::cout << "There is no such classes file or directory!" << std::endl;

	else
		std::cout << "Classes file has been opened successfully!" << std::endl;


    unsigned int numlines = 0;
    std::string readline;

    float pointxyval[788][2]; //[x][y]
    unsigned int id[numlines]; // Stores a given point's class.
    char tofloat[6];

    while (getline(data_file, readline) )
    {
        readline.copy(tofloat, 5, 0);
        for(unsigned int i = 0; i < 5; i++)
            if(tofloat[i] == '\t')
                tofloat[i] = NULL;
        pointxyval[numlines][0] = atof(tofloat);


        readline.copy(tofloat, 5, 5);
        for(unsigned int i = 0; i < 5; i++)
            if(tofloat[i] == '\t')
                tofloat[i] = NULL;
        pointxyval[numlines][1] = atof(tofloat);

        std::cout << tofloat << std::endl;
        //std::cout << readline << std::endl;
        numlines++;
    }

    numlines = 0;

    /*while (getline(data_file, readline) )
    {
        readline.copy(tofloat, 6, 0);
        std::cout << "Lal " << tofloat << std::endl;
        pointxyval[numlines][0] = atof(tofloat);
        //std::cout << "Array:" << pointxyval[numlines][0] << std::endl;
        numlines++;
    }*/

    numlines = 0;

    /*while (getline(classes_file, readline) )
    {
        //std::cout << readline << std::endl;

        //printf("Test:%c\n", readline.c_str());

        id[numlines] = atoi(readline.c_str());
        numlines++;
    }*/


    for(unsigned int i=0; i < 788; i++)
    {
        std::cout << "Array X:" << pointxyval[i][0] << " Array Y: " << pointxyval[i][1] << std::endl;
    }

}
