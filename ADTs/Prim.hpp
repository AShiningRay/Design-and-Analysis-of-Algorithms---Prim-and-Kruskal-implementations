#include<bits/stdc++.h>
#define Mem_end 0x3f3f3f3f

using namespace std;

typedef pair<int, int> Pairs;

class Graph_Prim
{
    int Vertex;
    list< pair<int, int> > *adjacency;

public:
    Graph_Prim(int Vertex);
    void put_edge(int vert1, int vert2, float weight);
    void calculates_Prim(int *classes);
};

Graph_Prim::Graph_Prim(int Vertex)
{
    this->Vertex = Vertex;
    adjacency = new list<Pairs> [Vertex];
}

void Graph_Prim::put_edge(int vert1, int vert2, float weight)
{
    adjacency[vert1].push_back(make_pair(vert2, weight));
    adjacency[vert2].push_back(make_pair(vert1, weight));
}

void Graph_Prim::calculates_Prim(int *classes)
{
    priority_queue< Pairs, vector <Pairs> , greater<Pairs> > priority_q;

    int origin = 0;

    vector<int> vertex_key(Vertex, Mem_end);

    vector<int> parent_vertex(Vertex, -1);

    vector<bool> inMST(Vertex, false);

    priority_q.push(make_pair(0, origin));
    vertex_key[origin] = 0;

    while (!priority_q.empty())
    {
        int vert1 = priority_q.top().second;
        priority_q.pop();

        inMST[vert1] = true;  // Include vertex in MST

        list< pair<int, int> >::iterator cont;
        for (cont = adjacency[vert1].begin(); cont != adjacency[vert1].end(); ++cont)
        {
            int vert2 = (*cont).first;
            float weight = (*cont).second;

            if (inMST[vert2] == false && vertex_key[vert2] > weight)
            {
                vertex_key[vert2] = weight;
                priority_q.push(make_pair(vertex_key[vert2], vert2));
                parent_vertex[vert2] = vert1;
            }
        }
    }

    for (int i = 1; i < Vertex; ++i){
        if (classes[parent_vertex[i]] != classes[i]){
            classes[parent_vertex[i]] = classes[i];
        }
        cout << parent_vertex[i] << " <-> " << i << endl;
    }
}

