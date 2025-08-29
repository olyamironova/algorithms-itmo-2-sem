#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int parent[10000];
int rk[10000];

void init_dsu() {
    for (int i = 0; i < 10000; i++) {
        parent[i] = i;
        rk[i] = 1;
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
        if (rk[ra] < rk[rb]) {
            parent[ra] = rb;
        } else if (rk[rb] < rk[ra]) {
            parent[rb] = ra;
        } else {
            parent[ra] = rb;
            rk[rb]++;
        }
        return true;
    }
}

int Kruskal(std::vector<std::pair<int, std::pair<int, int>>>& g, int n, std::pair<int, int> waste) {
    // вес, начало, конец
    init_dsu();
    int cost_mst = 0;
    int edge_count = 0;
    int u, v, c;
    for (auto& edge: g) {
        c = edge.first;
        u = edge.second.first;
        v = edge.second.second;

        if ((u == waste.first && v == waste.second) || (v == waste.first && u == waste.second)) {
            continue;
        }

        if (get_root(v) != get_root(u)) {
            merge(u, v);
            cost_mst += c;
            edge_count++;
        }
    }
    if (edge_count != n - 1) {
        return INT_MAX;
    } else {
        return cost_mst;
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, std::pair<int, int>>> g;
    int u, v, c;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v >> c;
        u--;
        v--;
        g.push_back({c, {u, v}});
    }
    std::sort(g.begin(), g.end());
    int first_mst = Kruskal(g, n, {-1, -1});
    int second_mst = INT_MAX;
    for (auto& edge: g) {
        int weight = Kruskal(g, n, edge.second);
        if (weight > first_mst && weight < second_mst) {
            second_mst = weight;
        }
    }
    std::cout << first_mst << " " << second_mst;
    return 0;
}