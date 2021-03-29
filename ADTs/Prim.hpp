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

            std::priority_queue < vertweightpair, std::vector <vertweightpair> , std::greater <vertweightpair> > priority_q;

            std::vector<float> vertex_key(vertex, ULONG_MAX); // Allocates a vector populated with the biggest value possible for a vertex's number
            std::vector<int> parent_vertex(vertex, -1); // Allocates a vector of integers containing a node's parent, which must also have its key as -1.
            std::vector<bool> inMST(vertex, false); // Allocates a vector of boolean values to check if a given vertex is in the Minimum Spanning Tree.

            int origin = 0;
            vertex_key[origin] = 0;
            priority_q.push( std::make_pair(0, origin) );

            while (!priority_q.empty())
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

            for (int i = 1; i < vertex; ++i)
                std::cout << "Prim verts: " << parent_vertex[i] << " <-> " << i << " || " << vertex_key[i] << std::endl;

            int j = 1, i = 0, group = 0, groups[k];;
            float tmp[k];

            /*while(j < 788) //Function to unite vertices. PS: A binary heap has been not implemented yet to collect the k highest values.
            {
                float tmp = 0;

                if (vertex_key[j] >= 1.27)
                {
                    classes[j-1] = t;
                    t++;
                }
                classes[j] = t;
                i++;
            }*/

            for (i = 0; i < k; i++)
            {
                tmp[i] = -1.0f;
                j = 1;
                while(j < 788) //Function to get the edges with the biggest cost.
                {
                    if(i == 0)
                    {
                        if (vertex_key[j] >= tmp[i])
                        {
                            tmp[i] = vertex_key[j];
                        }
                    }
                    else
                    {
                        if (vertex_key[j] >= tmp[i] && vertex_key[j] < tmp[i-1])
                        {
                            tmp[i] = vertex_key[j];
                        }
                    }
                    j++;
                }
            }

            printf("\n\n\n\n");

            for(int i = k-1; i >= 0; i--)
            { // prints the edges with biggest weights
                printf("%f, ", tmp[i]);
            }



            for (i = 0; i < k; i++)
            {
                j = 1;
                while(j < 788) //Function to find the positions in which the biggest cost edges are located.
                {
                    if (vertex_key[j] == tmp[k-1 - i])
                    {
                        classes[j-1] = group;
                        groups[i] = j-1;
                        group++;
                    }
                    classes[j] = group;
                    j++;
                }
            }

            for(i = 1; i < k; i++)
            {   // Orders the classes's positions on the array.
                int tmp;
                if(groups[i-1] > groups[i])
                {
                    tmp = groups[i];
                    groups[i] = groups[i-1];
                    groups[i-1] = tmp;
                }
            }

            for(i = 0; i < k; i++)
                printf("\n%d, ", groups[i]);

            for(int j = 0; j < k-1; j++)
                for(i = 0 + groups[j]; i < 788; i++) // Used to classify the vertices based on the positions found in the function above
                {
                    if(i >= groups[j] && i < groups[j+1])
                        classes[i] = j+1;
                    else if(i >= groups[j])
                        classes[i] = j+2;
                }



            write_results_file(classes); // O(n)
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
