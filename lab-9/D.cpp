#include <iostream>
#include <algorithm>
#include <valarray>

#define ull unsigned long long
const ull mod = std::pow(2, 64) + 7;
void FloydWarshall(ull** dist, int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != ULONG_LONG_MAX && dist[k][j] != ULONG_LONG_MAX && (dist[i][j] > (dist[i][k] + dist[k][j]))) {
                    if (dist[i][k] + dist[k][j] >= mod) {
                        dist[i][j] = ULONG_LONG_MAX;
                    } else {
                        dist[i][j] = (dist[i][k] + dist[k][j]) % mod;
                    }
                }
            }
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    ull** graph = new ull*[n];
    for (int i = 0; i < n; ++i) {
        graph[i] = new ull[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = ULONG_LONG_MAX;
            }
        }
    }
    int start, finish;
    ull cost;
    for (int i = 0; i < m; ++i) {
        std::cin >> start >> finish >> cost;
        --start;
        --finish;
        if (start != finish) {
            graph[start][finish] = std::min(graph[start][finish], static_cast<ull>(cost));
            graph[finish][start] = std::min(graph[finish][start], static_cast<ull>(cost));
        }
    }
    FloydWarshall(graph, n);
    ull* global_dist = new ull[n];
    for (int i = 0; i < n; ++i) {
        global_dist[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph[i][j] != ULONG_LONG_MAX && global_dist[i] + graph[i][j] >= mod) {
                global_dist[i] = ULONG_LONG_MAX;
                break;
            } else {
                global_dist[i] += graph[i][j] % mod;
            }
        }
    }
    std::pair<int, ull> ideal_house = std::make_pair(-1, ULONG_LONG_MAX);
    for (int i = 0; i < n; ++i) {
        if (global_dist[i] < ideal_house.second) {
            ideal_house.second = global_dist[i];
            ideal_house.first = i + 1;
        }
    }
    std::cout << ideal_house.first;

    for (int i = 0; i < n; ++i) {
        delete[] graph[i];
    }
    delete[] graph;
    delete[] global_dist;

    return 0;
}
