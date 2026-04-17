#include<bits/stdc++.h>
using namespace std;

// Dijkstra's implementation using priority queue
vector<int> dijkstra(int V, vector<vector<pair<int,int>>> &adj, int src) {

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    pq.push({0, src});
    while(!pq.empty()) {
        int dis = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        
        for(auto &it : adj[node]) {
            int edgeWeight = it.second;
            int adjNode = it.first;
            if(dis + edgeWeight < dist[adjNode]) {
                dist[adjNode] = dis + edgeWeight;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }

    return dist;
}


// Dijkstra's implementation using set
vector<int> dijkstra(int V, vector<vector<pair<int,int>>> &adj, int src) {

    set<pair<int,int>> st;
    st.insert({0, src});
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    while(!st.empty()) {
        int dis = st.begin()->first;
        int node = st.begin()->second;
        st.erase(st.begin());
        
        for(auto &it : adj[node]) {
            int edgeWeight = it.second;
            int adjNode = it.first;
            if(dis + edgeWeight < dist[adjNode]) {
                // Erase if it existed previously
                if(dist[adjNode] != INT_MAX) st.erase({dist[adjNode], adjNode});
                dist[adjNode] = dis + edgeWeight;
                st.insert({dist[adjNode], adjNode});
            }
        }
    }
    
    return dist;
}

int main() {

    return 0;
}