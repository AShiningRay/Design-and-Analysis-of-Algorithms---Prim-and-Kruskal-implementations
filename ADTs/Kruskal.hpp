#include <vector>
#include <algorithm>

typedef  std::pair<int, int> integer_pair; //Defines a type to describe a pair of integers, simplifying some std::vectors

class disjointSetUnion // Struct to simulate the Disjoint Set Union data structure.
{
    private:
    int *parentval = nullptr, *setrank = nullptr;
    int num = 0;

    public:
    disjointSetUnion(int num)
    {
        this->num = num; // Allocates the pointers and variables
        parentval = new int[num+1];
        setrank = new int[num+1];

        // "Sets" all vertices to different sets and assign 0 to them.
        for (int i = 0; i <= num; i++)
        {
            setrank[i] = 0;
            parentval[i] = i; //Makes it so that every single element is his own parentval(unique and only set)
        }
    }

    // Find the parent value of a given node
    int findParent(int u)
    {
        if (u != parentval[u])
            parentval[u] = findParent(parentval[u]);
        return parentval[u];
    }

    void uniteByRank(int val1, int val2) // Union of sets by rank
    {
        val1 = findParent(val1), val2 = findParent(val2);

        if (setrank[val1] > setrank[val2]) // If the first tree has a smaller height than the second one, make it a subtree of the taller
            parentval[val2] = val1;
        else // If the second tree has a smaller height than the first one, make it a subtree of the taller
            parentval[val1] = val2;

        if (setrank[val1] == setrank[val2])
            setrank[val2]++;
    }
};

class Graph_Kruskal // Struct used to simulate (i.e. Visually demonstrate) a graph
{
    private:
    int vertexnum = 0, edgenum = 0;
    std::vector< std::pair<float, integer_pair> > edgesvector{};

    public:
    Graph_Kruskal(int vertexnum, int edgenum)
    {
        this->vertexnum = vertexnum;
        this->edgenum = edgenum;
    }

    void addEdgeAndWeight(int vert1, int vert2, float weight)
    {
        edgesvector.push_back({weight, {vert1, vert2}}); // Adds an edge between vertexes
    }

    void kruskalAlgorithm(int *classes) // Executes the Algorithm of Kruskal
    {
        int mst_weightval = 0;

        // Sort the stack of edges ordered by cost
        sort(edgesvector.begin(), edgesvector.end());

        disjointSetUnion dsu(vertexnum);

        std::vector< std::pair<float, integer_pair> >::iterator edge_iteration;

        for (edge_iteration = edgesvector.begin(); edge_iteration != edgesvector.end(); edge_iteration++) // Check edge by edge to findParent the MST
        {
            int vert1 = edge_iteration->second.first;
            int vert2 = edge_iteration->second.second;

            int vert1_parent = dsu.findParent(vert1);
            int vert2_parent = dsu.findParent(vert2);

            if (vert1_parent != vert2_parent) // Checks if the selected edge creates a Cycle
            {

                if (classes[vert1] != classes[vert2]){
                    classes[vert1] = classes[vert2];
                }
                std::cout << "Kruskal verts: " << vert1 << " <-> " << vert2 << " || " << edge_iteration->first << std::endl; // Used to print the edge currently in the MST

                mst_weightval += edge_iteration->first; // Sum the weight of the path to the total weight of the MST

                dsu.uniteByRank(vert1_parent, vert2_parent);
            }
        }
    } // Finds the Minimum Spanning Tree using Kruskal's algorithm
};
