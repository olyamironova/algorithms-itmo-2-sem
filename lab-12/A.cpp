#include <bits/stdc++.h>

class Wall {

    struct Pin {
        long long x;
        long long y;
    };

    std::vector<Pin> pins;
    long long capacity;

    long long super_mega_hash(long long value){
        return (value % capacity);
    }

    bool find(std::vector<long long>& hash_table, long long value) {
        long long temp_hash = super_mega_hash(value);
        long long original_index = temp_hash;
        while (hash_table[temp_hash] != INT_MIN) {
            if (hash_table[temp_hash] == value) {
                return true;
            }
            temp_hash = (temp_hash + 1) % capacity;
            if (temp_hash == original_index)
                break;
        }
        return false;
    }

    void insert(std::vector<long long>& hash_table, long long value) {
        long long index = super_mega_hash(value);
        while (hash_table[index] != INT_MIN && hash_table[index] != value) {
            index = (index + 1) % capacity;
        }
        hash_table[index] = value;
    }

    void define_coordinate_axis(bool& line, char& flag, std::vector<long long>& axis_x, long long x, std::vector<long long>& axis_y, long long y) {
        if (!flag) {
            insert(axis_x, x);
        } else {
            insert(axis_y, y);
        }
        line = true;
    }

public:
    Wall(long long n): capacity(n) {}

    void insert_pin(long long x, long long y) {
        pins.push_back({x, y});
    }

    bool checking_three_strand() {
        for (char flag_one = 0; flag_one < 2; flag_one++) {
            for (char flag_two = 0; flag_two < 2; flag_two++) {
                for (char flag_three = 0; flag_three < 2; flag_three++) {
                    bool strand_one = false;
                    bool strand_two = false;
                    bool strand_three = false;
                    bool ans = true;
                    std::vector<long long> axis_x(capacity, INT_MIN);
                    std::vector<long long> axis_y(capacity, INT_MIN);
                    for (long long i = 0; i < capacity; ++i) {
                        if (find(axis_x, pins[i].x) || find(axis_y, pins[i].y)) {
                            continue;
                        } else {
                            if (!strand_one) {
                                define_coordinate_axis(strand_one, flag_one, axis_x, pins[i].x, axis_y, pins[i].y);

                            } else if (!strand_two) {
                                define_coordinate_axis(strand_two, flag_two, axis_x, pins[i].x, axis_y, pins[i].y);

                            } else if (!strand_three) {
                                define_coordinate_axis(strand_three, flag_three, axis_x, pins[i].x, axis_y, pins[i].y);
                            } else {
                                ans = false;
                            }
                        }
                    }
                    if (ans) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long n;
    std::cin >> n;
    Wall wall(n);
    long long x, y;
    for (long long i = 0; i < n; ++i) {
        std::cin >> x >> y;
        wall.insert_pin(x, y);
    }
    if (wall.checking_three_strand()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}