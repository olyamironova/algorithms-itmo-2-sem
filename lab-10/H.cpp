#include <iostream>
#include <vector>
#include <queue>

const int MAXN = 1000000;

std::vector<std::pair<int, int>> graph[MAXN];

int dijkstra(int start, int finish, int n) {
    std::vector<int> dist(n + 1, INT_MAX);
    dist[start] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist[finish] == INT_MAX ? -1 : dist[finish];
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    for (int i = 0; i < m; ++i) {
        int s, t, time;
        std::cin >> s >> time;
        std::vector<int> islands(s);
        for (int j = 0; j < s; ++j) {
            std::cin >> islands[j];
        }
        for (int j = 0; j < s; ++j) {
            for (int l = j + 1; l < s; ++l) {
                graph[islands[j]].push_back({islands[l], time});
                graph[islands[l]].push_back({islands[j], time});
            }
        }
    }

    std::cout << dijkstra(1, k, n);

    return 0;
}
