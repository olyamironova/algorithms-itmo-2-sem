#include <iostream>
#include <vector>

const int MAXN = 1000000;
int n;
std::vector<int> g[MAXN];
int parent[MAXN], degree[MAXN];

void dfs (int v) {
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (to != parent[v]) {
            parent[to] = v;
            dfs (to);
        }
    }
}

std::vector<int> prufer_code() {
    parent[n-1] = -1;
    dfs (n-1);

    int ptr = -1;
    for (int i=0; i<n; ++i) {
        degree[i] = (int) g[i].size();
        if (degree[i] == 1 && ptr == -1)
            ptr = i;
    }

    std::vector<int> result;
    int leaf = ptr;
    for (int iter=0; iter<n-2; ++iter) {
        int next = parent[leaf];
        result.emplace_back(next);
        --degree[next];
        if (degree[next] == 1 && next < ptr)
            leaf = next;
        else {
            ++ptr;
            while (ptr<n && degree[ptr] != 1)
                ++ptr;
            leaf = ptr;
        }
    }
    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int m;
    std::cin >> n >> m;
    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        --u;
        --v;
        g[v].emplace_back(u);
        g[u].emplace_back(v);
    }
    std::vector<int> result = prufer_code();
    for (int i = 0; i < n - 2; ++i) {
        std::cout << ++result[i] << " ";
    }
}
