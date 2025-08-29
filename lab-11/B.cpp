#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
#include "blazingio.hpp"

bool bfs(int** rGraph, int s, int t, int parent[], int n) {
    bool visited[n];
    memset(visited, 0, sizeof(visited));
    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[t];
}

int EdmondsKarp(int** graph, int s, int t, int n) {
    int u, v;
    int** rGraph = new int*[n];
    for (int i = 0; i < n; ++i) {
        rGraph[i] = new int[n];
    }
    for (u = 0; u < n; u++)
        for (v = 0; v < n; v++)
            rGraph[u][v] = graph[u][v];
    int parent[n];
    int max_flow = 0;
    while (bfs(rGraph, s, t, parent, n)) {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = std::min(path_flow, rGraph[u][v]);
        }
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    int** graph = new int*[n];
    for (int i = 0; i < n; ++i) {
        graph[i] = new int[n];
    }
    int a, b, c;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b >> c;
        a--;
        b--;
        graph[a][b] = c;
    }
    int ans = EdmondsKarp(graph, 0, n - 1, n);
    std::cout << ans;
}