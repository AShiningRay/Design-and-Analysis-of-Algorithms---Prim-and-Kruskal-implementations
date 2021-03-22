#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef  pair<int, int> paired_integer; //Defines a type to describe a pair of integers

class Graph // Struct used to simulate (i.e. Visually demonstrate) a graph
{
    public:
    int vertexnum = 0, edgenum = 0;
    vector< pair< pair<float, paired_integer>, int> > edgevector{};

    Graph(int vertexnum, int edgenum)
    {
        this->vertexnum = vertexnum;
        this->edgenum = edgenum;
    }

    void addEdgeAndWeight(int vert1, int vert2, float weight, int vertclass)
    {
        edgevector.push_back({{weight, {vert1, vert2}}, vertclass}); // Adds an edge between vertexes
    }

    void kruskalAlgorithm(); // Finds the MST using Kruskal's algorithm
};

struct DisjointSets // Struct to simulate the Disjoint Sets
{
    int *parentval = nullptr, *setrank = nullptr;
    int num = 0;

    DisjointSets(int num)
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

void Graph::kruskalAlgorithm() // Executes the Algorithm of Kruskal
{
    int mst_weightval = 0;

    // Sort the stack of edges ordered by cost
    sort(edgevector.begin(), edgevector.end());

    DisjointSets ds(vertexnum);

    vector< pair< pair<float, paired_integer>, int> >::iterator edge_iteration;

    for (edge_iteration = edgevector.begin(); edge_iteration!=edgevector.end(); edge_iteration++) // Check edge by edge to findParent the MST
    {
        int vert1 = edge_iteration->first.second.first;
        int vert2 = edge_iteration->first.second.second;

        int set_vert1 = ds.findParent(vert1);
        int set_vert2 = ds.findParent(vert2);

        if (set_vert1 != set_vert2) // Checks if the selected edge creates a Cycle
        {
            std::cout << vert1 << " <-> " << vert2 << " || " << edge_iteration->second << " || " << edge_iteration->first.first << std::endl; // Used to print the edge currently in the MST
            mst_weightval += edge_iteration->first.first; // Sum the weight of the path to the total weight of the MST

            ds.uniteByRank(set_vert1, set_vert2);
        }
    }
}
