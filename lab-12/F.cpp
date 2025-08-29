#include <iostream>
#include <bits/stdc++.h>

const int capacity = 1000000;

uint64_t getHash__1(const std::string& value, uint64_t tableCapacity) {
    uint64_t hash = 0;
    uint64_t p = 1004429;
    uint64_t m = 1003897;
    uint64_t p_pow = 1;

    for (char c : value) {
        hash = (hash + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    return hash % tableCapacity;
}

uint64_t getHash__2(const std::string& value, uint64_t tableCapacity) {
    uint64_t hash = 0;
    uint64_t p = 1000081;
    uint64_t m = 1003199;
    uint64_t p_pow = 1;

    for (char c : value) {
        hash = (hash + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    return hash % tableCapacity;
}

bool contains(const std::string& vec, char value) {
    for (auto el: vec) {
        if (el == value) {
            return true;
        }
    }
    return false;
}

bool lookup(const std::string& item, std::string& student, std::vector<std::pair<std::string, std::string>>& table_one, std::vector<std::pair<std::string, std::string>>& table_two) {
    uint64_t hashOne = getHash__1(item, capacity);
    uint64_t hashTwo = getHash__2(item, capacity);

    if(table_one[hashOne].first == item) {
        for (char value : student) {
            if (!contains(table_one[hashOne].second, value)) {
                table_one[hashOne].second.push_back(value);
            }
        }
        return true;
    }
    if(table_two[hashTwo].first == item) {
        for (char value : student) {
            if (!contains(table_two[hashTwo].second, value)) {
                table_two[hashTwo].second.push_back(value);
            }
        }
        return true;
    }

    return false;
}

void insert(std::string& key, std::string&& student, std::vector<std::pair<std::string, std::string>>& table_one, std::vector<std::pair<std::string, std::string>>& table_two) {
    bool found = false;
    uint64_t loopCount = 0;
    uint64_t initialHash = getHash__1(key, capacity);

    if(lookup(key, student, table_one, table_two))
        return;
    else {
        while(loopCount < 20 && !found) {
            if(table_one[initialHash].first.empty()) {
                table_one[initialHash] = std::make_pair(key, student);
                found = true;
            } else {
                std::pair<std::string, std::string> evictedValue = table_one[initialHash];
                table_one[initialHash] = std::make_pair(key, student);
                key = evictedValue.first;
                student = evictedValue.second;
                uint64_t newHash = getHash__2(key, capacity);
                if (table_two[newHash].first.empty() && newHash != initialHash) {
                    table_two[newHash] = {key, student};
                    found = true;
                    loopCount++;
                } else if (loopCount == 20) {
                    exit(1);
                }
            }
        }
    }
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t n;
    std::cin >> n;
    std::vector<std::pair<std::string, std::string>> table__1(capacity);
    std::vector<std::pair<std::string, std::string>> table__2(capacity);
    std::string enter;

    for (uint64_t i = 0; i < n; ++i) {
        std::cin >> enter;
        insert(enter, "0", table__1, table__2);
    }

    for (uint64_t i = 0; i < n; ++i) {
        std::cin >> enter;
        insert(enter, "1", table__1, table__2);
    }

    for (uint64_t i = 0; i < n; ++i) {
        std::cin >> enter;
        insert(enter, "2", table__1, table__2);
    }
    std::vector<uint64_t> e_balls(3, 0);
    for (auto it = table__1.begin(); it != table__1.end(); ++it) {
        if(!(*it).first.empty()) {
            if (((*it).second).size() == 1) {
                int8_t i = (*it).second[0] - '0';
                e_balls[i] += 3;
            } else if (((*it).second).size() == 2) {
                for (char value : (*it).second) {
                    int8_t i = value - '0';
                    e_balls[i] += 1;
                }
            }
        }
    }

    for (auto it = table__2.begin(); it != table__2.end(); ++it) {
        if(!(*it).first.empty()) {
            if (((*it).second).size() == 1) {
                int8_t i = (*it).second[0] - '0';
                e_balls[i] += 3;
            } else if (((*it).second).size() == 2) {
                for (char value : (*it).second) {
                    int8_t i = value - '0';
                    e_balls[i] += 1;
                }
            }
        }
    }
    for (auto &i: e_balls) {
        std::cout << i << " ";
    }
    return 0;
}