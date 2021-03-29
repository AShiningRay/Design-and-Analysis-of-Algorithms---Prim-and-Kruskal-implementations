#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <limits.h>

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
                        priority_q.push(std::make_pair(vertex_key[vert2], vert2)); // Pushes the pair (key, vertex) to the priority queue.
                        parent_vertex[vert2] = vert1; // Makes vert1 the parent of vert2.
                    }
                }
            }

            for (int i = 1; i < vertex; ++i)
                std::cout << "Prim verts: " << parent_vertex[i] << " <-> " << i << " || " << vertex_key[i] << std::endl;

            int i =1;
            int t = 0;
            while(i < 788) //Function to unite vertices. PS: A binary heap has been not implemented yet to collect the k highest values.
            {
                if (vertex_key[i] >= 1.27){
                    classes[i-1] = t;
                    t++;
                }
                classes[i] = t;
                i++;
            }

        }
};
