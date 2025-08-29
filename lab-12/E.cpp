#include <bits/stdc++.h>

long long super_mega_hash(long long e, long long i) {
    return e - i + 10e5;
}
int main() {
    long long n;
    long long ans = 0;
    std::cin >> n;
    std::vector<long long> s(11e5);
    long long e;
    for (long long i = 0; i < n; ++i) {
        std::cin >> e;
        ans += s[super_mega_hash(e, i)];
        s[super_mega_hash(e, i)]++;
    }
    std::cout << ans << "\n";
}