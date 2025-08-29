#include <bits/stdc++.h>

std::vector<size_t> computePrefixFunction(const std::string &pattern) {
    size_t m = pattern.length();
    std::vector<size_t> prefix(m, 0);
    size_t k = 0;

    for (size_t i = 1; i < m; i++) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = prefix[k - 1];
        }
        if (pattern[k] == pattern[i]) {
            k++;
        }
        prefix[i] = k;
    }
    return prefix;
}

std::vector<size_t> KMP(const std::string &text, const std::string &pattern) {
    std::vector<size_t> result;
    std::vector<size_t> prefix = computePrefixFunction(pattern);
    size_t n = text.length();
    size_t m = pattern.length();
    size_t q = 0;

    for (size_t i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i]) {
            q = prefix[q - 1];
        }
        if (pattern[q] == text[i]) {
            q++;
        }
        if (q == m) {
            result.push_back(i - m + 1);
            q = prefix[q - 1];
        }
    }
    return result;
}

int main() {
    std::string enter_data;
    std::string pattern;
    std::cin >> enter_data >> pattern;
    std::vector<size_t> indexes = KMP(enter_data, pattern);
    std::cout << indexes.size() << std::endl;
    for (size_t index : indexes) {
        std::cout << index << " ";
    }

    return 0;
}
