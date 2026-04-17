#include <bits/stdc++.h>
using namespace std;

int main() {
    int V = 5;

    // adjacency list: {node, weight}
    vector<vector<pair<int,int>>> adj(V);

    // undirected graph
    adj[0].push_back({1,2});
    adj[1].push_back({0,2});

    adj[0].push_back({3,6});
    adj[3].push_back({0,6});

    adj[1].push_back({2,3});
    adj[2].push_back({1,3});

    adj[1].push_back({4,5});
    adj[4].push_back({1,5});

    // min heap {weight, node}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    vector<int> vis(V, 0);

    pq.push({0, 0}); // start from node 0

    int sum = 0;

    while(!pq.empty()) {
        auto it = pq.top();
        pq.pop();

        int wt = it.first;
        int node = it.second;

        if(vis[node]) continue;

        vis[node] = 1;
        sum += wt;

        for(auto x : adj[node]) {
            if(!vis[x.first]) {
                pq.push({x.second, x.first});
            }
        }
    }

    cout << "MST Weight = " << sum;
}