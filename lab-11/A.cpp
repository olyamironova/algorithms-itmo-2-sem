#include <iostream>
#include <vector>
#include "blazingio.hpp"

int n, m;
std::vector<int> match;
std::vector<char> used_vertices;
bool is_okay(int i, int j, std::vector<std::vector<int>>& painting) {
    return ((i >= 0) && (j >= 0) && (i < n) && (j < m) && painting[i][j] != -1);
}

bool KuhnAlgorithm(int x, std::vector<std::vector<int>>& graph) {
    if (used_vertices[x]) {return false;}
    used_vertices[x] = true;
    for (int i = 0; i < graph[x].size(); ++i) {
        int to = graph[x][i];
        if ((match[to] == -1) || (KuhnAlgorithm(match[to], graph))) {
            match[to] = x;
            return true;
        }
    }
    return false;
}
int main() {
    int q;
    std::cin >> n >> m >> q;
    std::vector<std::vector<int>> painting(n, std::vector<int>(m));
    int c = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            painting[i][j] = c++;
        }
    }
    int a, b;
    for (int i = 0; i < q; ++i) {
        std::cin >> a >> b;
        a--;
        b--;
        painting[a][b] = -1;
    }
    std::vector<std::vector<int>> graph(n * m + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (painting[i][j] == -1) { continue;}
            if (is_okay(i - 1, j, painting)) {graph[painting[i][j]].push_back(painting[i - 1][j]);}
            if (is_okay(i + 1, j, painting)) {graph[painting[i][j]].push_back(painting[i + 1][j]);}
            if (is_okay(i, j - 1, painting)) {graph[painting[i][j]].push_back(painting[i][j - 1]);}
            if (is_okay(i, j + 1, painting)) {graph[painting[i][j]].push_back(painting[i][j + 1]);}
        }
    }
    match.assign(n * m, -1);
    for (int x = 0; x < n * m; ++x) {
        used_vertices.assign(n * m, false);
        KuhnAlgorithm(x, graph);
    }
    c = 0;
    for (int i = 0; i<n * m; ++i) {
        if (match[i] != -1) {
            c++;
        }
    }
    std::cout << c;
}