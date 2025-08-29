#include <iostream>
#include <unordered_map>
#include <vector>
int p[100000];
int rk[100000];

void init_dsu() {
    for (int i = 0; i < 100000; i++) {
        p[i] = i;
        rk[i] = 1;
    }
}

int get_root(int v) {
    if (p[v] == v) {
        return v;
    } else {
        return get_root(p[v]);
    }
}

bool merge(int a, int b) {
    int ra = get_root(a), rb = get_root(b);

    if (ra == rb) {
        return false;
    } else {
        if (rk[ra] < rk[rb]) {
            p[ra] = rb;
        } else if (rk[rb] < rk[ra]) {
            p[rb] = ra;
        } else {
            p[ra] = rb;
            rk[rb]++;
        }

        return true;
    }
}

void erase_adj(long long u, long long v, std::unordered_map<long long, std::unordered_map<long long, bool>>& matrix_of_adj) {
    matrix_of_adj[u].erase(v);
    matrix_of_adj[v].erase(u);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    long long n, m, q;
    std::cin >> n >> m >> q;
    std::vector<char> TypesOfRequest;
    std::vector<std::pair<int, int>> Requests;
    std::unordered_map<long long, std::unordered_map<long long, bool>> matrix_of_adj;
    long long u, v;
    for (long long i = 0; i < m; ++i) {
        std::cin >> u >> v;
        matrix_of_adj[u][v] = true;
        matrix_of_adj[v][u] = true;
    }
    char first_symbol;
    for (long long i = 0; i < q; ++i) {
        std::cin >> first_symbol;
        if (first_symbol == '?') {
            std::cin >> u >> v;
            TypesOfRequest.push_back('?');
            Requests.push_back(std::make_pair(u, v));
        } else /*if (first_symbol == '-')*/ {
            std::cin >> u >> v;
            TypesOfRequest.push_back('+');
            Requests.push_back(std::make_pair(u, v));
            erase_adj(u, v, matrix_of_adj);
        }
    }
    init_dsu();
    for (const auto& adj : matrix_of_adj) {
        for (const auto& edge : adj.second) {
            merge(adj.first, edge.first);
        }
    }
    std::vector<std::string> Answers;
    Answers.reserve(q);
    for (long long i = q - 1; i > -1; --i) {
        char type = TypesOfRequest[i];
        std::pair<int, int> v = Requests[i];
        if (type == '+') {
            merge(v.first, v.second);
        } else /*if (now_request.type_of_request == '?')*/ {
            if (get_root(v.first) == get_root(v.second)) {
                Answers.push_back("YES");
            } else {
                Answers.push_back("NO");
            }
        }
    }
    for (int i = Answers.size() - 1; i > -1; --i) {
        std::cout << Answers[i] << "\n";
    }
}
