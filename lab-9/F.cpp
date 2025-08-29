#include <iostream>
#include <vector>
#include <algorithm>

struct edge {
    long long a, b, cost;
};

void solve(long long n, long long m, long long k, std::vector<edge>& e) {
    std::vector<long long> d(n);
    std::vector<long long> p(n, -1);
    long long x;

    for (long long i = 0; i < n; ++i) {
        x = -1;
        for (long long j = 0; j < m; ++j) {
            if (d[e[j].b] > d[e[j].a] + e[j].cost) {
                d[e[j].b] = std::max(LONG_LONG_MIN, d[e[j].a] + e[j].cost);
                p[e[j].b] = e[j].a;
                x = e[j].b;
            }
        }
    }
    if (x == -1) {
        std::cout << "YES\n";
    } else {
        long long y = x;
        for (long long i = 0; i < n; ++i) {
            y = p[y];
        }
        
        std::vector<long long> path;
        for (long long temp = y; ; temp = p[temp]) {
            path.push_back(temp);
            if (temp == y && path.size() > 1) {
                break;
            }
        }

        if (path.size() <= k) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
}
int main() {
    long long N, k;
    std::cin >> N >> k;
    for (long long global_count = 0; global_count < N; ++global_count) {
        int n, m;
        std::cin >> n >> m;
        std::vector<edge> e;
        e.resize(m);
        for (long long i = 0; i < m; ++i) {
            std::cin >> e[i].a >> e[i].b >> e[i].cost;
            e[i].a--; e[i].b--;
        }
        solve(n, m, k, e);
    }

    return 0;
}
