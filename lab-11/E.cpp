#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include "blazingio.hpp"

using namespace std;

struct Edge {
    int a, b, capacity, flow = 0;

    Edge(int a, int b, int capacity) :
            a(a), b(b), capacity(capacity) {}

    int other(int v) const {
        return v == a ? b : a;
    }

    int capacityTo(int v) const {
        return v == b ? capacity - flow : flow;
    }

    void addFlowTo(int v, int deltaFlow) {
        flow += (v == b ? deltaFlow : -deltaFlow);
    }
};

struct Graph {
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<int> dist, edgeTo, index;

    bool bfs(int start, int finish) {
        dist.assign(graph.size(), 1e9);
        queue<int> q;

        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int e : graph[v]) {
                int to = edges[e].other(v);
                if (edges[e].capacityTo(to) && dist[to] > dist[v] + 1) {
                    dist[to] = dist[v] + 1;
                    q.push(to);
                }
            }
        }

        return dist[finish] != 1e9;
    }

    bool dfs(int v, int finish) {
        if (v == finish)
            return true;

        for ( ; index[v] < graph[v].size(); index[v]++) {
            int e = graph[v][index[v]], to = edges[e].other(v);
            if (edges[e].capacityTo(to) && dist[to] == dist[v] + 1 && dfs(to, finish)) {
                edgeTo[to] = e;
                return true;
            }
        }

        return false;
    }

    int neck_bottle(int start, int finish) {
        int min_capacity = 1e9;
        for (int v = finish; v != start; v = edges[edgeTo[v]].other(v))
            min_capacity = min(min_capacity, edges[edgeTo[v]].capacityTo(v));
        return min_capacity;
    }

    void addFlow(int start, int finish, int deltaFlow) {
        for (int v = finish; v != start; v = edges[edgeTo[v]].other(v))
            edges[edgeTo[v]].addFlowTo(v, deltaFlow);
    }

public:
    Graph(int vertexCount) :
            graph(vertexCount), dist(vertexCount), edgeTo(vertexCount), index(vertexCount) {}

    void addEdge(int from, int to, int capacity) {
        edges.emplace_back(Edge(from, to, capacity));
        graph[from].emplace_back(edges.size() - 1);
        graph[to].emplace_back(edges.size() - 1);
    }

    long long maxFlow(int start, int finish) {
        long long flow = 0;
        while (bfs(start, finish)) {
            index.assign(graph.size(), 0);
            while (dfs(start, finish)) {
                int deltaFlow = neck_bottle(start, finish);
                addFlow(start, finish, deltaFlow);
                flow += deltaFlow;
            }
        }
        return flow;
    }
};

struct Data {
    int an = 0, bn = 0;
    vector<pair<int, int>> edges;
};

Data processing_enter_data() {
    Data d;
    int edgeCount;
    int a, b;
    cin >> d.an >> d.bn >> edgeCount;

    d.edges.resize(edgeCount);
    for (int i = 0; i < edgeCount; ++i) {
        cin >> a >> b;
        a--;
        b--;
        d.edges[i] = {a, b};
    }
    return d;
}

Graph max_matching(Data &d) {
    Graph g(1 + d.an + d.bn + 1);

    for (int a = 0; a < d.an; a++)
        g.addEdge(0, 1 + a, 1);

    for (auto &[a, b] : d.edges)
        g.addEdge(1 + a, 1 + d.an + b, 1);

    for (int b = 0; b < d.bn; b++) {
        g.addEdge(1 + d.an + b, 1 + d.an + d.bn, 1);
    }
    g.maxFlow(0, 1 + d.an + d.bn);

    return g;
}

vector<vector<int>> minimal_vertex_cover(Data &d, Graph &g) {
    vector<vector<int>> mg(d.an + d.bn);
    for (auto &[a, b, _, flow] : g.edges) {
        if (0 != a && b != 1 + d.an + d.bn) {
            if (flow)
                mg[b - 1].emplace_back(a - 1);
            else
                mg[a - 1].emplace_back(b - 1);
        }
    }

    return mg;
}

void dfs(vector<vector<int>> &g, int v, vector<int> &visited) {
    visited[v] = 1;
    for (int to : g[v])
        if (!visited[to])
            dfs(g, to, visited);
}

pair<vector<int>, vector<int>> collect_minimal_vertex_cover(Data &d, vector<vector<int>> &g) {
    unordered_set<int> startVertices;
    for (int i = 0; i < d.an; i++)
        startVertices.insert(i);

    for (auto &row : g)
        for (int to : row)
            startVertices.erase(to);

    vector<int> visited(d.an + d.bn);
    for (int v : startVertices)
        dfs(g, v, visited);

    vector<int> a;
    for (int i = 0; i < d.an; i++)
        if (!visited[i])
            a.emplace_back(i);
    vector<int> b;
    for (int i = 0; i < d.bn; i++)
        if (visited[d.an + i])
            b.emplace_back(i);

    return { a, b };
}



int main() {
    auto d = processing_enter_data();
    auto g = max_matching(d);
    auto mg = minimal_vertex_cover(d, g);
    auto [a, b] = collect_minimal_vertex_cover(d, mg);
    if (a.empty()) {
        cout << a.size() << "\n\n";
    } else {
        cout << a.size() << "\n";
        for (auto x: a) {
            std::cout << x + 1 << " ";
        }
        std::cout << "\n";
    }
    if (b.empty()) {
        cout << b.size() << "\n\n";
    } else {
        cout << b.size() << "\n";
        for (auto x: b) {
            std::cout << x + 1 << " ";
        }
        std::cout << "\n";
    }
}
