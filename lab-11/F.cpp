#include <iostream>
#include <vector>
using namespace std;

class Graph {
    const int INF = 1e9;

    struct Edge {
        int a, b, capacity, flow = 0, cost;

        Edge(int a, int b, int capacity, int cost) :
                a(a), b(b), capacity(capacity), cost(cost) {}

        int other(int v) const {
            return v == a ? b : a;
        }

        int capacity_to(int v) const {
            return v == b ? capacity - flow : flow;
        }

        int cost_to(int v) const {
            return v == b ? cost : -cost;
        }

        void add_flow_to(int v, int deltaFlow) {
            flow += (v == b ? deltaFlow : -deltaFlow);
        }
    };

    vector<Edge> edges;
    vector<int> distTo;
    vector<int> edgeTo;

    void FordBellman(int start) {
        fill(distTo.begin(), distTo.end(), INF);
        distTo[start] = 0;
        while (true) {
            bool update = false;
            for (int i = 0; i < edges.size(); i++) {
                int a = edges[i].a, b = edges[i].b;
                if (edges[i].capacity_to(b) && distTo[a] != INF && distTo[b] > distTo[a] + edges[i].cost_to(b)) {
                    distTo[b] = distTo[a] + edges[i].cost_to(b);
                    edgeTo[b] = i;
                    update = true;
                }
                if (edges[i].capacity_to(a) && distTo[b] != INF && distTo[a] > distTo[b] + edges[i].cost_to(a)) {
                    distTo[a] = distTo[b] + edges[i].cost_to(a);
                    edgeTo[a] = i;
                    update = true;
                }
            }
            if (!update)
                break;
        }
    }

    bool exists_path(int start, int finish) {
        FordBellman(start);
        return distTo[finish] != INF;
    }

    int bottle_neck(int start, int finish) {
        int min_capacity = INF;
        for (int v = finish; v != start; v = edges[edgeTo[v]].other(v))
            min_capacity = min(min_capacity, edges[edgeTo[v]].capacity_to(v));
        return min_capacity;
    }

    long long add_flow(int start, int finish, int deltaFlow) {
        long long deltaCost = 0;
        for (int v = finish; v != start; v = edges[edgeTo[v]].other(v)) {
            edges[edgeTo[v]].add_flow_to(v, deltaFlow);
            deltaCost += deltaFlow * edges[edgeTo[v]].cost_to(v);
        }
        return deltaCost;
    }

public:
    Graph(int vertexCount) :
            distTo(vertexCount), edgeTo(vertexCount) {}

    void addEdge(int from, int to, int capacity, int cost) {
        edges.emplace_back(from, to, capacity, cost);
    }

    pair<long long, long long> minCostMaxFlow(int start, int finish) {
        long long cost = 0, flow = 0;
        while (exists_path(start, finish)) {
            int deltaFlow = bottle_neck(start, finish);
            cost += add_flow(start, finish, deltaFlow);
            flow += deltaFlow;
        }
        return { cost, flow };
    }
};

int main() {
    int n, m, s, t;
    int w_i, v_i, c_i, p_i;
    cin >> n >> m >> s >> t;
    --s; --t;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        cin >> w_i >> v_i >> c_i >> p_i;
        w_i--;
        v_i--;
        g.addEdge(w_i, v_i, c_i, p_i);
    }
    auto res = g.minCostMaxFlow(s, t);
    cout << res.second << " " << res.first;
}