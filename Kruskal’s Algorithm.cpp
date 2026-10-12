
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int src, dest, weight;
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

int findParent(vector<int>& parent, int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = findParent(parent, parent[i]);
}

void unionSet(vector<int>& parent, vector<int>& rank,
              int x, int y) {
    int rootX = findParent(parent, x);
    int rootY = findParent(parent, y);

    if (rootX == rootY)
        return;

    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

int main() {
    int V = 4;
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(V), rank(V, 0);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int totalWeight = 0;
    int count = 0;

    cout << "Edge\tWeight\n";

    for (Edge e : edges) {
        int x = findParent(parent, e.src);
        int y = findParent(parent, e.dest);

        if (x != y) {
            cout << e.src << " - " << e.dest
                 << "\t" << e.weight << endl;

            totalWeight += e.weight;
            unionSet(parent, rank, x, y);
            count++;

            if (count == V - 1)
                break;
        }
    }

    cout << "Total weight of MST: "
         << totalWeight << endl;

    return 0;
}
