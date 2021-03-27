#include <vector>
#include <algorithm>

typedef std::pair<int, int> integer_pair; //Defines a type to describe a pair of integers, simplifying some std::vectors

class disjointSetUnion // Class to simulate the Disjoint Set Union (aka. Union Find) data structure.
{
    private:
    int *parentnode = nullptr, *setrank = nullptr; // Allocates a pointer for a vertex's rank, and location of its parent
    int numverts = 0; // Amount of vertexes in the disjoint set data structure.

    public:
    disjointSetUnion(int numverts = 0) // Generates the Union sets.
    {
        this->numverts = numverts; // Allocates the pointers and variables
        parentnode = new int[numverts+1];
        setrank = new int[numverts+1];

        // Inserts all vertexes into different sets and assign their rank as 0.
        for (int i = 0; i <= numverts; i++)
        {
            setrank[i] = 0;
            parentnode[i] = i; //Makes it so that every single element is his own parentnode(basically a unique and only set)
        }
    }

    int findParent(int node)
    { // Find the parent of a given node
        if (node != parentnode[node])
            parentnode[node] = findParent(parentnode[node]);

        return parentnode[node];
    }

    void uniteByRank(int val1, int val2) // Union of sets by rank
    {
        val1 = findParent(val1), val2 = findParent(val2);

        if (setrank[val1] > setrank[val2]) // If the first tree has a smaller height than the second one, make it a subtree of the taller one.
            parentnode[val2] = val1;
        else // If the second tree has a smaller height than the first one, make it a subtree of the taller one.
            parentnode[val1] = val2;

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
    Graph_Kruskal(int vertexnum, int edgenum) // Creates the Kruskal's Graph, passing the number of edges and vertexes.
    {
        this->vertexnum = vertexnum;
        this->edgenum = edgenum;
    }

    void addEdgeAndWeight(int vert1, int vert2, float weight)
    {
        edgesvector.push_back({weight, {vert1, vert2}}); // Adds an edge between vertexes
    }

    void kruskalAlgorithm(int *classes, int k) // Calculates the Minimum Spanning Tree using Kruskal's algorithm
    {
        int mst_weightval = 0; // Defines the initial total weight of the MST.


        sort(edgesvector.begin(), edgesvector.end()); // Sort the stack of edges ordered by cost

        disjointSetUnion dsu(vertexnum); // Creates a Disjoint Set Union with the total amount of vertexes

        std::vector< std::pair<float, integer_pair> >::iterator edge_iteration; // Allocates a vector of edges between vertexes to be used as as a iterator below

        for (edge_iteration = edgesvector.begin(); edge_iteration != edgesvector.end(); edge_iteration++) // Check edge by edge to find its parent in the MST
        {
            int vert1 = edge_iteration->second.first;
            int vert2 = edge_iteration->second.second;

            int vert1_parent = dsu.findParent(vert1);
            int vert2_parent = dsu.findParent(vert2);

            if (vert1_parent != vert2_parent) // Checks if the selected edge creates a Cycle between the vertex parents.
            {

                union_vertex(vert1, vert2, classes, k);

                std::cout << "Kruskal verts: " << vert1 << " <-> " << vert2 << " || " << edge_iteration->first << std::endl; // Used to print the edge currently in the MST

                mst_weightval += edge_iteration->first; // Sum the weight of the path to the total weight of the MST

                dsu.uniteByRank(vert1_parent, vert2_parent); //Unite both vertexes linked by the edge in the data structure's tree.
            }
        }
    }

    void union_vertex(int vert1, int vert2, int *classes, int k)
    {
        if (classes[vert1] != classes[vert2])
        {

        }
    }
};
