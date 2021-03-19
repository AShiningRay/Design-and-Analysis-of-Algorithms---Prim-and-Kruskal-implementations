#include "ADTs/Prim.hpp"
#include "ADTs/Kruskal.hpp"

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    fstream data_file, classes_file;
    data_file.open("./Files/dados.txt", ios::in);
    classes_file.open("./Files/classes.txt", ios::in);


    if (!data_file)
		cout << "No such data file or directory!" << endl;

	else
		cout << "Data file opnened successfully!" << endl;

    if (!classes_file)
		cout << "No such classes file or directory!" << endl;

	else
		cout << "Classes file opnened successfully!" << endl;



    string readline;

    while (getline(data_file, readline) )
        cout << readline << endl;

}
