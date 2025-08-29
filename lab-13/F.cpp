#include <bits/stdc++.h>
#include <regex>

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore();
    std::regex data_regex(("^[A-Z][a-z]+ [A-Z][a-z]+ [A-Z][a-z]+ \\d{2} ((8|\\+7)[\\- ]?)?(\\(?\\d{3}\\)?[\\- ]?)?[\\d\\- ]{7,10} g\\.[A-Z]{3}, ul\\.[A-Z][a-z]+, d\\.\\d{1,}$"));
    for(int i = 0; i < n; ++i) {
        std::string data;
        std::getline(std::cin, data);
        if (std::regex_match(data, data_regex)) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}
