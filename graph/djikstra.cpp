#include <bits/stdc++.h>
using namespace std;

int shortestPath(int n, vector<vector<int>>& edges, int source, int destination) {
    vector<vector<pair<int, int>>> graph(n);
    for (const auto& edge : edges) {
        graph[edge[0]].emplace_back(edge[1], edge[2]);
        graph[edge[1]].emplace_back(edge[0], edge[2]); // For undirected graph
    }

    vector<int> dist(n, INT_MAX);
    dist[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& [v, weight] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist[destination] == INT_MAX ? -1 : dist[destination];
}