#include <iostream>
#include <vector>


class Graph {
private:
    bool** adjacent;
    int m;
public:
    Graph(int edges): m(edges) {
        adjacent = new bool*[edges];
        for (int i = 0; i < edges; ++i) {
            adjacent[i] = new bool[edges];
            for (int j = 0; j < edges; ++j) {
                adjacent[i][j] = false;
            }
        }
    };
    void add_edges(int a, int b) {
        adjacent[a][b] = true;
        adjacent[b][a] = true;
    }

    bool exist(int a, int b) {
        return adjacent[a][b];
    }
};
int main() {
    std::vector<int> v;
    int n, m;
    std::cin >> n >> m;
    Graph g(n);
    int a, b;
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b;
        g.add_edges(a, b);
        bool flag_a = false;
        for (auto x: v) {
            if (x == a) {
                flag_a = true;
            }
        }
        if (!flag_a) { v.push_back(a);}
        bool flag_b = false;
        for (auto x: v) {
            if (x == b) {
                flag_b = true;
            }
        }
        if (!flag_b) { v.push_back(b);}
    }
    for (int k = 0; k < n; ++k) {
        if (!g.exist(v.at(0), v.at(1))) {
            int i = 2;
            while ((!g.exist(v.at(0), v.at(i))) or (!g.exist(v.at(1), v.at(i + 1)))) {
                i++;
            }
            // v.swapSubQueue(1, i);
            for (int j = 0; j < ((i - 1) / 2) + 1; ++j) {
                std::swap(v[1 + k], v[i - k]);
            }
        }
        v.push_back(v.front());
        v.erase(v.begin());
    }
    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << " ";
    }
}