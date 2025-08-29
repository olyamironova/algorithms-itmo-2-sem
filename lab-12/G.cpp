#include <bits/stdc++.h>

uint64_t get_hash(std::vector<uint64_t>& value, uint64_t table_capacity) {
    uint64_t hash = 0;
    uint64_t p = 1004429;
    uint64_t m = 1003897;
    uint64_t p_pow = 1;
    for (uint64_t c : value) {
        hash = (hash + c * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash % table_capacity;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t n;
    std::cin >> n;
    std::vector<std::pair<uint64_t, uint64_t>> edges1(n - 1), edges2(n - 1);
    for (uint64_t i = 0; i < n - 1; ++i) {
        std::cin >> edges1[i].first >> edges1[i].second;
    }
    for (uint64_t i = 0; i < n - 1; ++i) {
        std::cin >> edges2[i].first >> edges2[i].second;
    }

    std::vector<uint64_t> degrees1(n + 1, 0);
    std::vector<uint64_t> degrees2(n + 1, 0);

    for (const auto& edge : edges1) {
        ++degrees1[edge.first];
        ++degrees1[edge.second];
    }

    for (const auto& edge : edges2) {
        ++degrees2[edge.first];
        ++degrees2[edge.second];
    }
    std::sort(degrees1.begin(), degrees1.end());
    std::sort(degrees2.begin(), degrees2.end());

    uint64_t hash_one = get_hash(degrees1, n + 1);
    uint64_t hash_two = get_hash(degrees2, n + 1);
    if (hash_one == hash_two) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}
