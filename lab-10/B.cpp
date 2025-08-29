#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> parent, rank;

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int main() {
    int n, m;
    std::vector<Edge> edges;
    std::cin >> n >> m;
    int u, v, c;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v >> c;
        --u;
        --v;
        Edge new_edge(u, v, c);
        edges.emplace_back(new_edge);
    }
    int cost = 0;
    std::vector<Edge> result;
    parent.resize(n);
    rank.resize(n);
    for (int i = 0; i < n; i++)
        make_set(i);

    std::sort(edges.begin(), edges.end());

    for (Edge e : edges) {
        if (find_set(e.u) != find_set(e.v)) {
            cost += e.weight;
            
            union_sets(e.u, e.v);
        }
    }

    std::cout << cost;
}