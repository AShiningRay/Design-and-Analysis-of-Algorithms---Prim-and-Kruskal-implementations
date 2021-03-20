#include <vector>
#include <queue>
#include <cstdlib>
#include <iostream>

#define INFINITO DBL_MAX
#define VERDE 0
#define AMARELO 1
#define VERMELHO 2
#define NULO -1
#include <limits.h>
#include <stdbool.h>
#define V 10

/*
typedef pair<int, int> primintpair;
typedef vector<primintpair> vecprimintpair;
*/
typedef double tpeso;
typedef int tvertice;
typedef int tapontador;
int vet[5000];

typedef struct{
int mat[100][100];
int num_vertices;
tvertice antecessor[100];
} tgrafo;

struct taresta{
tpeso peso;
tvertice orig, dest;

bool operator <(const taresta &a) const {
    return peso>a.peso;
    }
};

class Prim
{
    /*
    public:
        std::priority_queue<primintpair, vector<primintpair>, greater<primintpair>> primorityqueue; // Here's our binary priority queue for the weights


    Prim(int source_node, vector<primintpair> *nodegraph)
    {
        int minspantree_cost = 0;
        primorityqueue.push(make_pair(0, source_node));
        bool addednodes[nodegraph.size()];

        memset(addednode, false, sizeof(bool) *nodegraph.size());

    }
    */

    public:
    void inserearesta(tvertice v, tvertice u, tpeso peso, tgrafo *grafo){
        grafo->mat[v][u] = peso;
    }
    tapontador proximoadj(tvertice v, tapontador aux, tgrafo *grafo){

        for (aux++; aux<grafo->num_vertices; aux++){
            if (grafo->mat[v][aux] != 0)
                return aux;
            }
        return (int) NULL;
    }

    tapontador primeiroadj(tvertice v, tgrafo *grafo){
        tapontador aux;

        for (aux = 0; aux < grafo->num_vertices; aux++){
            if (grafo->mat[v][aux] != 0){
            return aux;
            }
        }
        return (int) NULL;
    }

    taresta cria_aresta(tpeso peso, tvertice orig, tvertice dest){
        taresta aresta;
        aresta.peso = peso;
        aresta.orig = orig;
        aresta.dest = dest;
        return aresta;
    }

    void inicializagrafo(tgrafo *grafo, int num_vertices){
        int i, j;
        grafo->num_vertices = num_vertices;
        for (i=0; i<grafo->num_vertices; i++){
            for (j=0; j<grafo->num_vertices; j++){
                grafo->mat[i][j] = (rand() % 9);
            }
        }
    }

    void recuperaadj(tvertice v, tapontador p, tvertice *u, tpeso *peso, tgrafo *grafo){
        *u = p;
        *peso = grafo->mat[v][p];
    }

    void prim(tvertice v, tgrafo *grafo, tgrafo *agm){
        std::priority_queue<taresta> heap;
        tpeso peso; tvertice u, w; tapontador p;
        int i, marc[100];

        inicializagrafo(agm, grafo->num_vertices);

        for (i=0; i<grafo->num_vertices; i++){
            marc[i] = VERDE;
        }

        marc[i] = VERMELHO;

        p = primeiroadj(v, grafo);

        while(p != NULO){
            recuperaadj(v, v, &w, &peso, grafo);
            heap.push(cria_aresta(peso, v, w));
            p = proximoadj(v, p, grafo);
            std::cout << "finished." << std::endl;
        }

        while(!heap.empty()){

            v = heap.top().orig;
            w = heap.top().dest;
            peso = heap.top().peso;
            heap.pop();

            if (marc[w] == VERMELHO) continue;
            inserearesta(v, w, peso, agm);
            marc[w] = VERMELHO;
            p = primeiroadj(w, grafo);

            while(p != NULO){
                recuperaadj(w, p, &u, &peso, grafo);
                heap.push(cria_aresta(peso, w, u));
                p = proximoadj(w, p, grafo);

            }
        }
    }
};
