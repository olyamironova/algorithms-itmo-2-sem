#include <iostream>
#include <vector>
#include <algorithm>

bool compare(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

void bridge_help(int u, int parent, std::vector<bool>& visited, std::vector<int>& disc, std::vector<int>& low, int& count_, std::vector<std::vector<int>>& adj, std::vector<std::pair<int, int>>& ans) {
    visited[u] = true;
    disc[u] = ++count_;
    low[u] = count_;
    for (int v : adj[u]) {
        if (!visited[v]) {
            bridge_help(v, u, visited, disc, low, count_, adj, ans);

            low[u] = std::min(low[u], low[v]);

            if (low[v] > disc[u]) {
                ans.push_back(std::make_pair(std::min(u, v) + 1, std::max(u, v) + 1));
            }
        } else if (v != parent)
            low[u] = std::min(low[u], disc[v]);
    }
}

void find_bridges(int n, std::vector<bool>& visited, std::vector<int>& disc, std::vector<int>& low,  int& count_, std::vector<std::vector<int>>& adj,  std::vector<std::pair<int, int>>& ans) {
    visited.assign(n, false);
    disc.assign(n, 0);
    low.assign(n, 0);

    for (int i = 0; i < n; i++)
        if (!visited[i])
            bridge_help(i, -1, visited, disc, low, count_, adj, ans);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adj;
    std::vector<bool> visited;
    std::vector<int> disc, low;
    std::vector<std::pair<int, int>> ans;
    int count_ = 0;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    find_bridges(n, visited, disc, low, count_, adj, ans);
    std::sort(ans.begin(), ans.end(), &compare);
    for (int i = 0; i < ans.size(); ++i) {
        std::cout << ans[i].first << " " << ans[i].second << "\n";
    }
    return 0;
}
