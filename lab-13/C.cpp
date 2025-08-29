#include <bits/stdc++.h>

std::vector<size_t> z_function(const std::string& s) {
    size_t n = s.length();
    std::vector<size_t> z(n, 0);
    size_t l = 0;
    size_t r = 0;
    for (size_t i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t n, m;
    std::cin >> n >> m;
    std::cin.ignore();
    std::string text;
    getline(std::cin, text);
    size_t counter = 0;
    size_t i, j, k;
    for (size_t w = 0; w < m; w++) {
        std::cin >> i >> j >> k;
        i--;
        j--;
        if (i + k > n || j + k > n) {
            continue;
        }
        if (i == j) {
            counter++;
            continue;
        }
        std::string combined = text.substr(i, k) + "#" + text.substr(j, k);
        std::vector<size_t> z = z_function(combined);
        if (z[k + 1] >= k) {
            counter++;
        }
    }
    std::cout << counter;
    return 0;
}