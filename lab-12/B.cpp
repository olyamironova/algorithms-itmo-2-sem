#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;
const int capacity = 100000;
const int primary_numbers[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
        73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
        179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
        283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
        419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
        547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
        661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
        811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
        947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
        1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223
};


uint64_t super_mega_hash(const vector<uint64_t>& line, size_t begin, size_t end) {
    uint64_t hash = 1;
    for (size_t i = begin; i <= end; ++i) {
        hash *= primary_numbers[line[i]];
    }
    return hash;
}

bool find(vector<vector<uint64_t>>& hash_table, uint64_t value) {
    uint64_t hash_percent = value % capacity;
    for (auto element: hash_table[hash_percent]) {
        if (element == value) {
            return true;
        }
    }
    return false;
}

int main() {
    vector<vector<uint64_t>> hash_table(capacity);
    uint64_t n;
    cin >> n;
    vector<uint64_t> table_one(n);
    for (size_t i = 0; i < n; ++i) {
        cin >> table_one[i];
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i; j < n; ++j) {
            uint64_t hash = super_mega_hash(table_one, i, j);
            uint64_t hash_percent = hash % capacity;
            hash_table[hash_percent].push_back(hash);
        }
    }
    uint64_t m;
    cin >> m;
    vector<uint64_t> table_two(m);
    for (size_t i = 0; i < m; ++i) {
        cin >> table_two[i];
    }
    int max_l = INT_MIN;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = i; j < m; ++j) {
            uint64_t hash = super_mega_hash(table_two, i, j);
            if (find(hash_table, hash)) {
                max_l = max(max_l, static_cast<int>(j - i + 1));
            }
        }
    }
    cout << max_l;
}
