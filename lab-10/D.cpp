#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

const int MAXN = 1000000;
std::vector<int> graph[MAXN];
std::vector<std::pair<int, int>> edges;
std::vector<int> my_stack;
bool visited[MAXN]{0};

void dfs(int v) {
    while (!graph[v].empty()) {
        int u = graph[v].back();
        graph[v].pop_back();
        for (auto it = graph[u].begin(); it != graph[u].end(); ++it) {
            if (*it == v) {
                graph[u].erase(it);
                break;
            }
        }
        dfs(u);
    }
    my_stack.push_back(v);
}

int main() {
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.push_back({u, v});
    }
    for (int i = 0; i < n; ++i) {
        std::reverse(graph[i].begin(), graph[i].end());
    }
    int count_odd = 0;
    for (int i = 0; i < n; ++i) {
        if (graph[i].size() % 2 != 0) {
            count_odd++;
        }
    }

    // все компоненты связности кроме одной не содержат ребер
    int count_big_comp = 0;
    for (int i = 0; i < n; ++i) {
        if (visited[i]) {
            continue;
        }
        if (graph[i].size() == 0) {
            continue;
        }
        count_big_comp++;
        std::queue<int> q;
        q.push(i);
        visited[i] = true;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to: graph[v]) {
                if (visited[to]) {
                    continue;
                }
                q.push(to);
                visited[to] = true;
            }
        }
    }
    if (count_odd == 0 && count_big_comp == 1) {
    } else {
        std::cout << ":(\n";
        return 0;
    }

    dfs(0);
    if (my_stack[0] == 0 && my_stack.size() == 1) {
        std::cout << ":(\n";
        return 0;
    }
    std::vector<int> euler_cycle;
    for (int i = my_stack.size() - 1; i > -1; --i) {
        std::cout << my_stack[i] + 1 << " ";
    }

    return 0;
}