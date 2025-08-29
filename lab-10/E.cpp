#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

const int MAXN = 3000000;
std::vector<int> graph[MAXN];
int tin[MAXN], up[MAXN], colors[MAXN];
int time_, maxColor;
std::stack<int> st;

void paint(int v) {
    maxColor++;
    int last = -1;
    while (last != v && !st.empty()) {
        colors[st.top()] = maxColor;
        last = st.top();
        st.pop();
    }
}

void dfs(int v, int p) {
    time_++;
    tin[v] = time_;
    up[v] = time_;
    st.push(v);
    for (int u : graph[v]) {
        if (u == p) continue; // если обратное ребро
        if (tin[u]) {
            up[v] = std::min(up[v], tin[u]);
        } else {
            dfs(u, v);
            up[v] = std::min(up[v], up[u]);
            if (up[u] > tin[v]) {
                paint(u);
            }
        }
    }
    if (p == -1) paint(v); // если мы в корне
}

int main() {
    int n, m, q;
    std::cin >> n >> m >> q;
    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(0, -1); // запускаемся от корня дерева dfs

    for (int i = 0; i < q; ++i) {
        std::cin >> u >> v;
        if (colors[u] == colors[v]) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}
