#include <vector>
#include <algorithm>
#include <fstream>

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
        if (node != parentnode[node]) //O(1)
            parentnode[node] = findParent(parentnode[node]);

        return parentnode[node];
    }

    void unionByRank(int val1, int val2) // Union of sets by rank
    {
        val1 = findParent(val1), val2 = findParent(val2);

        if (setrank[val1] > setrank[val2]) // If the first tree has a smaller height than the second one, make it a subtree of the taller one.
            parentnode[val2] = val1;

        else // If the second tree has a smaller height than the first one, make it a subtree of the taller one.
            parentnode[val1] = val2;


        if (setrank[val1] == setrank[val2])
            setrank[val2]++;
    }

    int getAmountOfClusters()
    { //Return the number of groups created. O(E+2V)
		int cont = 0, i = 0, arr[numverts];
		bool repeated = false;

		for (int i = 0; i < numverts; i ++) // Complexity: O(V)
            arr[i] = -1;
        i = 0;
		while(i < numverts)
        { // This algorithm will run through all edges, so it will be O(E)
	        for (int j = 0; j < i; j++)
                if(arr[j] == parentnode[i])
                    repeated = true;

            if(repeated == false)
                arr[i] = parentnode[i];

            i++;
            repeated = false;
	    }

	    for(i=0; i < numverts; i ++)
        { //O(V)
            if(arr[i] != -1)
                cont++;
        }

		return cont;
	}

    void printGroups(int *classes)
    { //Print the groups values on the screen.
	    bool repeated = false;
	    int i = 0, arr[numverts];

	    for(i=0; i < numverts; i++)
            arr[i] = -1;

        i=0;

	    while(i < numverts)
        {
            classes[i] = parentnode[i];
	        for (int j = 0; j < i; j++)
                if(arr[j] == parentnode[i])
                    repeated = true;

            if(repeated == false) arr[i] = parentnode[i];

            i++;
            repeated = false;
	    }

	    for(i=0; i < numverts; i ++)
        {
            if(arr[i] != -1)
                std::cout << "Class: " << arr[i] << std::endl;
        }
	}

    //Function to save the results in a txt file.
	void write_results_file()
    {
        std::ofstream file ("./Results/results_kruskal.txt");

        if (file.is_open())
        { // O(n)
            for (int i=0; i<numverts; i++){
            file << parentnode[i];
            if (i < numverts-1)
                file << "\n";
            }
            file.close();
        }
        else std::cout << "Unable to open file";
        }
};

class Graph_Kruskal // Struct used to simulate (i.e. Visually demonstrate) a graph
{
    private:
    int vertexnum = 0, edgenum = 0;
    std::vector< std::pair<float, integer_pair> > edgesvector{};

    public:
    Graph_Kruskal(int vertexnum, int edgenum) // Creates the Kruskal's Graph, passing the number of edges and vertices.
    {
        this->vertexnum = vertexnum;
        this->edgenum = edgenum;
    }

    void addEdgeAndWeight(int vert1, int vert2, float weight)
    {
        edgesvector.push_back({weight, {vert1, vert2}}); // Adds an edge between vertices
    }

    void kruskalAlgorithm(int *classes, int k) // Calculates the Minimum Spanning Tree using Kruskal's algorithm
    {
        int mst_weightval = 0; // Defines the initial total weight of the MST.


        /*Simplified sorting algorithm, the push back is still up there, but the actual sorting can now be viewed in a more straightforward way,
        instead of being with the edge insertion and placement. According to the C++ STL, it's complexity is O(NlogN), but since kruskal deals with
        edges, the complexity is O(ElogE), sorting the edges in the stack by its cost.
        */
        sort(edgesvector.begin(), edgesvector.end());

        disjointSetUnion dsu(vertexnum); // Creates a Disjoint Set Union with the total amount of vertices

        std::vector< std::pair<float, integer_pair> >::iterator edge_iteration; // Allocates a vector of edges between vertices to be used as as a iterator below

        for (edge_iteration = edgesvector.begin(); edge_iteration != edgesvector.end(); edge_iteration++) // Check edge by edge to find its parent in the MST
        { // Runs through all edges, which means that it has the upper bound complexity of O(E * (E+2V)), due to its nested function to check the amount of clusters.
            if(k == dsu.getAmountOfClusters()) // From the function analysis, we have the time complexity of O(E+2V)
                break;

            int vert1 = edge_iteration->second.first;
            int vert2 = edge_iteration->second.second;

            int vert1_parent = dsu.findParent(vert1);
            int vert2_parent = dsu.findParent(vert2);

            if (vert1_parent != vert2_parent) // Checks if the selected edge creates a Cycle between the vertex parents.
            {
                std::cout << "Kruskal verts: " << vert1 << " <-> " << vert2 << " || " << edge_iteration->first << std::endl; // Used to print the edge currently in the MST

                mst_weightval += edge_iteration->first; // Sum the weight of the path to the total weight of the MST

                dsu.unionByRank(vert1_parent, vert2_parent); //Unite both vertices linked by the edge in the data structure's tree.
            }
        }
        dsu.printGroups(classes); // Optional, hence, its complexity was not calculated, but if needed, the complexity is nearly the same as the getAmountOfClusters
        dsu.write_results_file(); // O(n)
    }
};
