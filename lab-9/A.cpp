#include <iostream>
#include <stack>
#include <vector>

void make_set (int v, int* parent, int* rank) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v, int* parent) {
    if (v == parent[v]) {
        return v;
    }
    return find_set(parent[v], parent);
}

void union_sets (int a, int b, int* parent, int* rank) {
    a = find_set(a, parent);
    b = find_set(b, parent);
    if (a != b) {
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            ++rank[a];
    }
}

struct request {
    char type_of_request;
    int start;
    int finish;
};

void erase_adj(int u, int v, std::vector<std::pair<int, int>>& matrix_of_adj) {
    for (auto pair = matrix_of_adj.begin(); pair != matrix_of_adj.end(); ++pair) {
        if ((*pair).first == u && (*pair).second == v) {
            matrix_of_adj.erase(pair);
            break;
        }
    }

    for (auto pair = matrix_of_adj.begin(); pair != matrix_of_adj.end(); ++pair) {
        if ((*pair).first == v && (*pair).second == u) {
            matrix_of_adj.erase(pair);
            break;
        }
    }
}

int main() {
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<request> Requests;
    std::vector<std::pair<int, int>> matrix_of_adj(m);
    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        matrix_of_adj.emplace_back(u, v);
        matrix_of_adj.emplace_back(v, u);
    }
    char first_symbol;
    for (int i = 0; i < q; ++i) {
        std::cin >> first_symbol;
        if (first_symbol == '?') {
            std::cin >> u >> v;
            request new_request('?', u, v);
            Requests.push_back(new_request);
        } else if (first_symbol == '-') {
            std::cin >> u >> v;
            request new_request('-', u, v);
            Requests.push_back(new_request);
            erase_adj(u, v, matrix_of_adj);
        }
    }
    int* rank = new int[n + 1];
    int* parent = new int[n + 1];
    for (int i = 0; i < n + 1; ++i) {
        make_set(i, parent, rank);
    }
    for (int i = 0; i < matrix_of_adj.size(); ++i) {
        union_sets(matrix_of_adj[i].first, matrix_of_adj[i].second, parent, rank);
    }
    std::vector<std::string> Answers;
    for (int i = q - 1; i > -1; --i) {
        request now_request = Requests[i];
        if (now_request.type_of_request == '-') {
            union_sets(now_request.start, now_request.finish, parent, rank);
        } else if (now_request.type_of_request == '?') {
            if (find_set(now_request.start, parent) == find_set(now_request.finish, parent)) {
                Answers.emplace_back("YES");
            } else {
                Answers.emplace_back("NO");
            }
        }
    }
    for (int i = Answers.size() - 1; i > -1; --i) {
        std::cout << Answers[i] << "\n";
    }
}