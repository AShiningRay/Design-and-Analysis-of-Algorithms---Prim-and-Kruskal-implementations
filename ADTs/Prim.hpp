#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <limits.h>
#include <fstream>

typedef std::pair<int, float> vertweightpair; //Defines a type to describe a pair made of a integer and a float, simplifying some std::vectors

class Graph_Prim
{
    private:
        int vertex = 0; // How many vertexes
        std::list< vertweightpair > *adjacency{};

    public:
        Graph_Prim(int vertex)
        {
            this->vertex = vertex;
            adjacency = new std::list<vertweightpair> [vertex]; // Prepares the list of adjacencies.
        }

        void put_edge(int vert1, int vert2, float weight) // Creates an weighed edge between a pair of passed vertexes.
        {
            adjacency[vert1].push_back(std::make_pair(vert2, weight));
            adjacency[vert2].push_back(std::make_pair(vert1, weight));
        }

        void calculate_Prim(int k, int *classes) // Where Prim's Minimum Spanning Tree is calculated.
        {
            float vector_dist[788];
            std::priority_queue < vertweightpair, std::vector <vertweightpair> , std::greater <vertweightpair> > priority_q;

            std::vector<float> vertex_key(vertex, ULONG_MAX); // Allocates a vector populated with the biggest value possible for a vertex's number
            std::vector<int> parent_vertex(vertex, -1); // Allocates a vector of integers containing a node's parent, which must also have its key as -1.
            std::vector<bool> inMST(vertex, false); // Allocates a vector of boolean values to check if a given vertex is in the Minimum Spanning Tree.

            int origin = 0;
            vertex_key[origin] = 0;
            priority_q.push( std::make_pair(0, origin) );
            while (!priority_q.empty()) //Complexity O(E log V)
            {
                int vert1 = priority_q.top().second;
                priority_q.pop(); // Removes the current node from the priority queue.

                inMST[vert1] = true;  // Include the vertex in the MST

                std::list < vertweightpair >::iterator vertex_iterator;

                for (vertex_iterator = adjacency[vert1].begin(); vertex_iterator != adjacency[vert1].end(); ++vertex_iterator)
                {
                    int vert2 = (*vertex_iterator).first; // Finds the second vertex of the pair
                    float weight = (*vertex_iterator).second; // Gets the weight of the edge between both vertexes

                    if (inMST[vert2] == false && vertex_key[vert2] > weight)
                    {
                        vertex_key[vert2] = weight; // Sets the edge weight as the second vertex's key
                        priority_q.push(std::make_pair(vertex_key[vert2], vert2)); // Pushes the pair (weight, vertex) to the priority queue.
                        parent_vertex[vert2] = vert1; // Makes vert1 the parent of vert2.
                    }
                }
            }


            for (int i = 1; i < vertex; ++i){
                std::cout << "Prim verts: " << parent_vertex[i] << " <-> " << i << " || " << vertex_key[i] << std::endl;
                vector_dist[i] = vertex_key[i]; //Sotage the weights in a different array.
            }

            shellSort(vector_dist, 788); //Shellsort will sort the numbers in ascending order.

            float biggest[k-1]; //Creates an array to storage the biggest edges.
            int t=0;
            int i = 787;

            //Finds and storages the buggest edges in the end of the array sorted by shellsort. Complexity O(k - 1)
            while(i > (787 - (k-1))){
                biggest[t] = vector_dist[i];
                t++;
                i--;
            }

            t = 0;
            int j=0;
            float valor;

            while(j < 788) //Function to unite vertices. Complexity ((v - 1) * (k - 1))
            {
                valor = vertex_key[j];
                if (check(valor, k-1, biggest) == 1) //Send the values to check() function compares if vertex_key[j] is one of the biggest edges.
                {
                    classes[j-1] = t;
                    t++;
                }
                classes[j] = t;
                j++;
            }
            write_results_file(classes); //Wirte results on a file
        }

        void shellSort(float *vet, int size_vet) { //"Its complexity cannot be ascertained.
            int i , j;
            float value_aux;
            int t = 1;
            while(t < size_vet) {
                t = 3*t+1;
            }
            while ( t > 1) {
                t /= 3;
                for(i = t; i < size_vet; i++) {
                    value_aux = vet[i];
                    j = i - t;
                    while (j >= 0 && value_aux < vet[j]) {
                    vet [j + t] = vet[j];
                    j -= t;
                    }
                    vet [j + t] = value_aux;
                }
            }
        }

        //Function that will check if a number of vertex_key is equal to some of value of k. Complexity O(k - 1)
        int check(float valor, int k, float *biggest){
            for (int i=0; i<k; i++){
                if (valor == biggest[i])
                    return 1;
            }
            return 0;
        }

        //Function to save the results in a txt file.
        void write_results_file(int *classes)
        {
            std::ofstream file ("./Results/results_prim.txt");

            if (file.is_open())
            {
                for (int i=0; i<788; i++){
                file << classes[i];
                if (i < 787)
                    file << "\n";
                }
                file.close();
            }
            else std::cout << "Unable to open file";
        }
};
