#include<bits/stdc++.h>
#define Mem_end 0x3f3f3f3f

typedef std::pair<int, float> vertweightpair;

class Graph_Prim
{
    int vertex;
    std::list< std::pair<int, float> > *adjacency;

public:
    Graph_Prim(int vertex);
    void put_edge(int vert1, int vert2, float weight);
    void calculates_Prim(int *classes);
};

Graph_Prim::Graph_Prim(int vertex)
{
    this->vertex = vertex;
    adjacency = new std::list<vertweightpair> [vertex];
}

void Graph_Prim::put_edge(int vert1, int vert2, float weight)
{
    adjacency[vert1].push_back(std::make_pair(vert2, weight));
    adjacency[vert2].push_back(std::make_pair(vert1, weight));
}

void Graph_Prim::calculates_Prim(int *classes)
{
    std::priority_queue< vertweightpair, std::vector <vertweightpair> , std::greater<vertweightpair> > priority_q;

    std::vector<float> vertex_key(vertex, Mem_end);
    std::vector<int> parent_vertex(vertex, -1);
    std::vector<bool> inMST(vertex, false);

    int origin = 0;
    vertex_key[origin] = 0;
    priority_q.push(std::make_pair(0, origin));

    while (!priority_q.empty())
    {
        int vert1 = priority_q.top().second;
        priority_q.pop();

        inMST[vert1] = true;  // Include vertex in MST

        std::list< std::pair<int, float> >::iterator cont;
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

    for (int i = 1; i < vertex; ++i){
        if (classes[parent_vertex[i]] != classes[i])
            classes[parent_vertex[i]] = classes[i];

    std::cout << "Prim verts: " << parent_vertex[i] << " <-> " << i << " || " << vertex_key[i] << std::endl;
    }
}

