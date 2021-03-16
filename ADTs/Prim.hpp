#include <vector>
#include <queue>

typedef pair<int, int> primintpair;
typedef vector<primintpair> vecprimintpair;

class Prim
{
    public:
        std::priority_queue<primintpair, vector<primintpair>, greater<primintpair>> primorityqueue; // Here's our binary priority queue for the weights


    Prim(int source_node, vector<primintpair> *nodegraph)
    {
        int minspantree_cost = 0;
        primorityqueue.push(make_pair(0, source_node));
        bool addednodes[nodegraph.size()];

        memset(addednode, false, sizeof(bool) *nodegraph.size());

    }

    private:

        void test()
        {

            return;
        }
};
