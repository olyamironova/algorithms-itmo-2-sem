#include <iostream>
#include <list>
#include <queue>

class Graph {
private:
    int n;
    std::vector<std::vector<std::pair<int, int>>> adjacent;

public:
    Graph(int n) {
        this->n = n;
        adjacent.resize(n);
    }

    void AddEdge(int a, int b, int t) {
        adjacent[a].push_back(std::make_pair(b, t));
    }

    void Dijkstra() {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::less<std::pair<int, int>>> heap;
        std::vector<int> dist(n, INT_MAX);
        heap.push(std::make_pair(0, 0));
        dist[0] = 0;
        while (!heap.empty()) {
            int u = heap.top().second;
            heap.pop();
            std::vector<std::pair<int, int>>::iterator it;
            for (it = adjacent[u].begin(); it != adjacent[u].end(); ++it) {
                int v = (*it).first;
                int weight = (*it).second;
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    heap.push(std::make_pair(dist[v], v));
                }
            }
        }
        if (dist[n - 1] > 900000) {
            std::cout << -1;
        } else {
            std::cout << dist[n - 1];
        }

    }


};
int main() {
    int connection, roads;
    std::cin >> connection >> roads;
    int a, b, t;
    Graph graph(connection);
    for (int i = 0; i < roads; ++i) {
        std::cin >> a >> b >> t;
        graph.AddEdge(--a, --b, t);
    }
    graph.Dijkstra();
}