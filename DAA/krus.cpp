#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;

    DSU(int n) {
        parent.resize(n);
        for(int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if(parent[x] == x) return x;
        return find(parent[x]); // no path compression needed (simple version)
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if(a != b) {
            parent[b] = a; // simple union
        }
    }
};

int main() {
    int V = 4;

    // {weight, u, v}
    vector<tuple<int,int,int>> edges = {
        {10,0,1},
        {6,0,2},
        {5,0,3},
        {15,1,3},
        {4,2,3}
    };

    sort(edges.begin(), edges.end());

    DSU dsu(V);

    int mstWeight = 0;

    for(auto [wt, u, v] : edges) {
        if(dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            mstWeight += wt;
        }
    }

    cout << "MST Weight = " << mstWeight;
}