#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef  pair<int, int> pairedInteger; //Defines a type to describe a pair of integers

class Graph // Struct used to simulate (i.e. Visually demonstrate) a graph
{
    public:
    int vertexnum, edgenum;
    vector< pair<int, pairedInteger> > edgevector;

    Graph(int vertexnum, int edgenum)
    {
        this->vertexnum = vertexnum;
        this->edgenum = edgenum;
    }

    void addEdgeAndWeight(int vert1, int vert2, int weight)
    {
        edgevector.push_back({weight, {vert1, vert2}}); // Adds an edge between vertexes
    }

    int kruskalAlgorithm(); // Finds the MST using Kruskal's algorithm
};

struct DisjointSets // Struct to simulate the Disjoint Sets
{
    int *parentval, *setrank;
    int num;

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
    int find(int u)
    {
        if (u != parentval[u])
            parentval[u] = find(parentval[u]);
        return parentval[u];
    }

    void merge(int val1, int val2) // Union of sets by rank
    {
        val1 = find(val1), val2 = find(val2);

        if (setrank[val1] > setrank[val2]) // If the first tree has a smaller height than the second one, make it a subtree of the taller
            parentval[val2] = val1;
        else // If the second tree has a smaller height than the first one, make it a subtree of the taller
            parentval[val1] = val2;

        if (setrank[val1] == setrank[val2])
            setrank[val2]++;
    }
};

int Graph::kruskalAlgorithm() // Executes the Algorithm of Kruskal
{
    int mst_weightval = 0;

    // Sort the stack of edges ordered by cost
    sort(edgevector.begin(), edgevector.end());

    DisjointSets ds(vertexnum);

    vector< pair<int, pairedInteger> >::iterator iteration;

    for (iteration=edgevector.begin(); iteration!=edgevector.end(); iteration++) // Check edge by edge to find the MST
    {
        int vert1 = iteration->second.first;
        int vert2 = iteration->second.second;

        int set_vert1 = ds.find(vert1);
        int set_vert2 = ds.find(vert2);

        if (set_vert1 != set_vert2) // Checks if the selected edge creates a Cycle
        {
            printf("%d <-> %d || %d\n",vert1, vert2, iteration->first); // Used to print the edge currently in the MST

            mst_weightval += iteration->first; // Sum the weight of the path to the total weight of the MST

            ds.merge(set_vert1, set_vert2);
        }
    }
    return mst_weightval;
}
