#include <bits/stdc++.h>

std::vector<int> prefix_function(const std::string& s) {
    size_t n = s.size();
    std::vector<int> p(n);
    p[0] = 0;
    for (size_t i = 1; i < n; ++i) {
        int k = p[i - 1];
        while (k > 0 && s[i]!= s[k]) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            k++;
        }
        p[i] = k;
    }
    return p;
}

int main() {
    std::string s;
    std::cin >> s;
    auto p = prefix_function(s);
    for (size_t i = 0; i < s.size(); ++i) {
        std::cout << p[i] << " ";
    }
    return 0;
}
