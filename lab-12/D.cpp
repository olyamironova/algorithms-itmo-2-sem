#include <iostream>
#include <bits/stdc++.h>

long long super_mega_hash(long long value) {
    return value;
}

class BinarySearchTree {
public:

    long long Average() {
        std::pair<long long, long long> sum_counter = std::make_pair(0, 0);
        find_average(root, sum_counter);
        return sum_counter.first / sum_counter.second;
    }

    long long GetMax() {
        long long max_e_ball = LONG_LONG_MIN;
        find_max_for_n(root, max_e_ball);
        return max_e_ball;
    }

    void Insert(std::pair<long long, long long> value) {
        root = insert(root, value);
        FixHeight(root);
    }

    void Delete(long long isu) {
        root = delete_key(root, isu);
    }

    long long GetRootBalance() {
        if (root) {
            return root->balance;
        } else {
            return 0;
        }
    }

    bool Empty() {
        return is_empty();
    }

    struct Node {
        Node* left_child;
        Node* right_child;
        std::pair<long long, long long> isu_points;
        long long height;
        long long balance;
        Node(std::pair<long long, long long> isu_points) : left_child(nullptr), right_child(nullptr), height(1), balance(0), isu_points(std::move(isu_points)) {}
    };
    Node* root = nullptr;

private:
    void find_average(Node* temp_node, std::pair<long long, long long>& sum_counter) {
        if (temp_node == nullptr) {
            return;
        }
        sum_counter.first += temp_node->isu_points.second;
        sum_counter.second++;
        find_average(temp_node->left_child, sum_counter);
        find_average(temp_node->right_child, sum_counter);
    }

    bool is_empty() {
        return (!root);
    }

    long long Height(Node* temp_node) {
        if (temp_node) {
            return temp_node->height;
        } else {
            return 0;
        }
    }

    long long BalanceFactor(Node* temp_node) {
        if (temp_node) {
            return Height(temp_node->right_child) - Height(temp_node->left_child);
        } else {
            return 0;
        }
    }

    void FixHeight(Node* temp_node) {
        long long height1 = Height(temp_node->left_child);
        long long height2 = Height(temp_node->right_child);
        temp_node->height = std::max(height1, height2) + 1;
        temp_node->balance = BalanceFactor(temp_node);
    }

    Node* RotateRight(Node* temp_node) {
        Node* new_peak = temp_node->left_child;
        temp_node->left_child = new_peak->right_child;
        new_peak->right_child = temp_node;
        FixHeight(temp_node);
        FixHeight(new_peak);
        return new_peak;
    }

    Node* RotateLeft(Node* temp_node) {
        Node* new_peak = temp_node->right_child;
        temp_node->right_child = new_peak->left_child;
        new_peak->left_child = temp_node;
        FixHeight(temp_node);
        FixHeight(new_peak);
        return new_peak;
    }

    Node* Balance(Node* temp_node) {
        if (temp_node != nullptr) {
            FixHeight(temp_node);
            if (BalanceFactor(temp_node) == 2) {
                if (BalanceFactor(temp_node->right_child) < 0) {
                    temp_node->right_child = RotateRight(temp_node->right_child);
                }
                temp_node = RotateLeft(temp_node);
            }
            if (BalanceFactor(temp_node) == -2) {
                if (BalanceFactor(temp_node->left_child) > 0) {
                    temp_node->left_child = RotateLeft(temp_node->left_child);
                }
                temp_node = RotateRight(temp_node);
            }
        }
        return temp_node;
    }

    Node* insert(Node* future_parent, std::pair<long long, long long> isu_points) {
        if (future_parent == nullptr) {
            return new Node(isu_points);
        }
        if (isu_points.first < future_parent->isu_points.first) {
            future_parent->left_child = insert(future_parent->left_child, isu_points);
        } else if (isu_points.first > future_parent->isu_points.first) {
            future_parent->right_child = insert(future_parent->right_child, isu_points);
        } else {

        }
        return Balance(future_parent);
    }

    Node* find_max(Node* p) {
        Node* temp_node = p;
        while (temp_node && temp_node->right_child) {
            temp_node = temp_node->right_child;
        }
        return temp_node;
    }

    void find_max_for_n(Node* temp_node, long long& max_points) {
        if (temp_node == nullptr) {
            return;
        }
        if (temp_node->isu_points.second > max_points) {
            max_points = temp_node->isu_points.second;
        }
        find_max_for_n(temp_node->left_child, max_points);
        find_max_for_n(temp_node->right_child, max_points);
    }

    Node* delete_key(Node* root, long long isu) {
        if (root == nullptr) {
            return root;
        }
        if (isu < root->isu_points.first) {
            root->left_child = delete_key(root->left_child, isu);
        } else if (isu > root->isu_points.first) {
            root->right_child = delete_key(root->right_child, isu);
        } else {
            if (root->left_child == nullptr) {
                Node* temp = root->right_child;
                delete root;
                return Balance(temp);
            } else if (root->right_child == nullptr) {
                Node* temp = root->left_child;
                delete root;
                return Balance(temp);
            }

            Node* temp = find_max(root->left_child);
            root->isu_points = temp->isu_points;
            root->left_child = delete_key(root->left_child, temp->isu_points.first);
        }

        return Balance(root);
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<BinarySearchTree> hash_table;
    hash_table.resize(n + 1);
    std::string first_symbol;
    int number_of_group, isu, points;
    for (int i = 0; i < q; ++i) {
        std::cin >> first_symbol;
        if (first_symbol == "+") {
            std::cin >> number_of_group >> isu >> points;
            hash_table[super_mega_hash(number_of_group)].Insert(std::make_pair(isu, points));
        } else if (first_symbol == "-") {
            std::cin >> number_of_group >> isu;
            hash_table[super_mega_hash(number_of_group)].Delete(isu);
        } else if (first_symbol == "m") {
            std::cin >> number_of_group;
            long long max_e_ball = hash_table[super_mega_hash(number_of_group)].GetMax();
            std::cout << max_e_ball << "\n";
        } else if (first_symbol == "a") {
            std::cin >> number_of_group;
            long long average = hash_table[super_mega_hash(number_of_group)].Average();
            std::cout << average << "\n";
        }
    }
}