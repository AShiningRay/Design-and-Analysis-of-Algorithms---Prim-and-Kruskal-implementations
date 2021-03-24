#include <iostream>
#include <list>
#include <queue>
#include <vector>

typedef std::pair<int, float> vertweightpair; //Defines a type to describe a pair made of a integer and a float, simplifying some std::vectors

class Graph_Prim
{
    private:
        int vertex = 0;
        std::list< vertweightpair > *adjacency{};

    public:
        Graph_Prim(int vertex)
        {
            this->vertex = vertex;
            adjacency = new std::list<vertweightpair> [vertex];
        }

        void put_edge(int vert1, int vert2, float weight)
        {
            adjacency[vert1].push_back(std::make_pair(vert2, weight));
            adjacency[vert2].push_back(std::make_pair(vert1, weight));
        }

        void calculate_Prim(int *classes) // Where Prim's Minimum Spanning Tree is calculated.
        {
            std::priority_queue < vertweightpair, std::vector <vertweightpair> , std::greater <vertweightpair> > priority_q;

            std::vector<float> vertex_key(vertex, ULONG_MAX); // Allocates a vector populated with the biggest value possible for a vertex's key
            std::vector<int> parent_vertex(vertex, -1);
            std::vector<bool> inMST(vertex, false); // Allocates a vector of boolean values to check if a given vertex is in the Minimum Spanning Tree.

            int origin = 0;
            vertex_key[origin] = 0;
            priority_q.push( std::make_pair(0, origin) );

            while (!priority_q.empty())
            {
                int vert1 = priority_q.top().second;
                priority_q.pop(); // Removes the current node from the priority queue.

                inMST[vert1] = true;  // Include the vertex in the MST

                std::list < vertweightpair >::iterator cont;

                for (cont = adjacency[vert1].begin(); cont != adjacency[vert1].end(); ++cont)
                {
                    int vert2 = (*cont).first;
                    float weight = (*cont).second;

                    if (inMST[vert2] == false && vertex_key[vert2] > weight)
                    {
                        vertex_key[vert2] = weight;
                        priority_q.push(std::make_pair(vertex_key[vert2], vert2));
                        parent_vertex[vert2] = vert1;
                    }
                }
            }

            for (int i = 1; i < vertex; ++i)
            {
                if (classes[parent_vertex[i]] != classes[i])
                    classes[parent_vertex[i]] = classes[i];

                std::cout << "Prim verts: " << parent_vertex[i] << " <-> " << i << " || " << vertex_key[i] << std::endl;
            }
        }
};
