#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <set>

int parent[300000], rank[300000];

void init_dsu() {
    for (int i = 0; i < 300000; i++) {
        parent[i] = i;
        rank[i] = 1;
    }
}

int get_root(int v) {
    if (parent[v] == v) {
        return v;
    } else {
        return parent[v] = get_root(parent[v]);
    }
}

bool merge(int a, int b) {
    int ra = get_root(a), rb = get_root(b);
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



void dfs(int x, std::vector<int>& a, std::vector<int>& b, std::vector<int>& c, std::vector<std::vector<std::pair<int, int>>>& graph, int n, int parent) {
    for (auto neighbour: graph[x]) {
        if (neighbour.first == parent) {
            continue;
        }
        dfs(neighbour.first, a, b, c, graph, n, x);
        a[x] = std::max(a[x], b[neighbour.first] + neighbour.second - c[neighbour.first]);
        b[x] += c[neighbour.first];
    }
    a[x] += b[x];
    c[x] = std::max(a[x], b[x]);
}

struct Graph {
    struct Edge {
        int start;
        int finish;
        int weight;
        bool operator<(Edge& other) {
            return weight < other.weight;
        }
    };

    std::vector<Graph::Edge> edge_list;
    void add_edge(int a, int b, int c) {
        Graph::Edge new_edge{a, b, c};
        edge_list.emplace_back(new_edge);
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    int u, v, c_;
    Graph complex_graph;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v >> c_;
        --u;
        --v;
        complex_graph.add_edge(u, v, c_);
    }
    std::vector<std::vector<std::pair<int, int>>> result(n);
    init_dsu();
    std::sort(complex_graph.edge_list.begin(), complex_graph.edge_list.end());
    for (auto& e : complex_graph.edge_list) {
        if (get_root(e.start) != get_root(e.finish)) {
            merge(e.start, e.finish);
            result[e.start].push_back({e.finish, e.weight});
            result[e.finish].push_back({e.start, e.weight});
        }
    }
    std::vector<int> a(n, 0);
    std::vector<int> b(n, 0);
    std::vector<int> c(n, 0);
    dfs(0, a, b, c, result, n, -1);
    std::cout << std::max(c[0], std::max(a[0], b[0]));
    return 0;
}