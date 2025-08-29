#include <iostream>
#include <vector>
#include <algorithm>

long long parent[600000], rank[600000];

void init_dsu() {
    for (long long i = 0; i < 600000; i++) {
        parent[i] = i;
        rank[i] = 1;
    }
}

long long get_root(long long v) {
    if (parent[v] == v) {
        return v;
    } else {
        return parent[v] = get_root(parent[v]);
    }
}

bool merge(long long a, long long b) {
    long long ra = get_root(a), rb = get_root(b);
    if (ra == rb) {
        return false;
    } else {
        if (rank[ra] < rank[rb]) {
            parent[ra] = rb;
        } else if (rank[rb] < rank[ra]) {
            parent[rb] = ra;
        } else {
            parent[ra] = rb;
            rank[rb]++;
        }
        return true;
    }
}

struct Edge {
    long long u, v, weight;
    bool visited;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long n, m;
    std::vector<Edge> edges;
    std::cin >> n >> m;
    long long u, v, c;
    for (long long i = 0; i < m; ++i) {
        std::cin >> u >> v >> c;
        --u;
        --v;
        Edge new_edge(u, v, c);
        edges.emplace_back(new_edge);
    }
    long long cost = 0;
    std::vector<Edge> result;
    init_dsu();

    std::sort(edges.begin(), edges.end());

    for (Edge& e : edges) {
        if (get_root(e.u) != get_root(e.v)) {
            if (!e.visited) {cost += e.weight; e.visited = true;}
            merge(e.u, e.v);
        }
    }
    std::cout << cost;
}