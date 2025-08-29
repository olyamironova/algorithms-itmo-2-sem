#include <iostream>
#include <vector>

int parent[300000];
int rk[300000];

class BinarySearchTree {
public:
    void Insert(int value) {
        amount_nodes++;
        root = insert(root, value);
    }

    int kthLargest(int k) {
        Node* x = jump_traverse(root, k, 0);
        if (x != nullptr) {
            return x->value;
        } else {
            return 0;
        }
    }
    struct Node {
        Node *left_child;
        Node *right_child;
        int value;
        int amount_element;

        Node(int Value) : left_child(nullptr), right_child(nullptr), value(Value), amount_element(1) {}
    };

    Node *root = nullptr;
    int amount_nodes = 0;
    
    Node* search(Node* temp_node, int value) {
        if (temp_node == nullptr || value == temp_node->value) {
            return temp_node;
        }
        if (value < temp_node->value) {
            return search(temp_node->left_child, value);
        } else {
            return search(temp_node->right_child, value);
        }
    }

    void AmountFactor(Node* temp_node) {
        int left_amount;
        int right_amount;
        if (temp_node->left_child != nullptr) {
            left_amount = temp_node->left_child->amount_element;
        } else {
            left_amount = 0;
        }
        if (temp_node->right_child != nullptr) {
            right_amount = temp_node->right_child->amount_element;
        } else {
            right_amount = 0;
        }
        temp_node->amount_element = left_amount + right_amount + 1;
    }

    Node *insert(Node *future_parent, int value) {
        if (future_parent == nullptr) {
            return new Node(value);
        } else if (value < future_parent->value) {
            future_parent->left_child = insert(future_parent->left_child, value);
        } else if (value > future_parent->value) {
            future_parent->right_child = insert(future_parent->right_child, value);
        }
        AmountFactor(future_parent);
        return future_parent;
    }

    Node* jump_traverse(Node* temp_node, const int& k, int visited) {
        int l;
        if (temp_node->left_child == nullptr) {
            l = 0;
        } else {
            l = (temp_node->left_child)->amount_element;
        }
        if ((visited + l >= k) && (temp_node->left_child != nullptr)) {
            return jump_traverse(temp_node->left_child, k, visited);
        } else if (visited + l == k - 1) {
            return temp_node;
        } else if ((visited + l < k - 1) && (temp_node->right_child != nullptr)) {
            return jump_traverse(temp_node->right_child, k, visited + l + 1);
        }
    }

    void Merge(BinarySearchTree& other) {
        if (other.root != nullptr) {
            inorder_merge(other.root);
        }
    }

    void inorder_merge(Node* temp_node) {
        if (temp_node != nullptr) {
            inorder_merge(temp_node->left_child);
            Insert(temp_node->value);
            parent[temp_node->value] = root->value;
            inorder_merge(temp_node->right_child);
        }
    }

    void deleteTree(Node* temp_node) {
        if (temp_node == nullptr) return;
        deleteTree(temp_node->left_child);
        deleteTree(temp_node->right_child);
        delete temp_node;
    }
};

std::vector<BinarySearchTree> galaxy;

void init_dsu() {
    for (int i = 0; i < 300000; i++) {
        parent[i] = i;
        rk[i] = 1;
    }
}

int get_root(int v) {
    if (parent[v] == v) {
        return v;
    } else {
        return parent[v] = get_root(parent[v]);
    }
}

bool merge(int a, int b) {
    int root_a = get_root(a), root_b = get_root(b);
    if (root_a == root_b) {
        return false;
    } else {
        if (rk[root_a] < rk[root_b]) {
            galaxy[root_b].Merge(galaxy[root_a]);
        } else if (rk[root_b] < rk[root_a]) {
            galaxy[root_a].Merge(galaxy[root_b]);
        } else {
            galaxy[root_b].Merge(galaxy[root_a]);
            rk[root_b]++;
        }
        return true;
    }
}
int main() {
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    int n, q;
    std::cin >> n >> q;
    galaxy.reserve(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        BinarySearchTree bst;
        bst.Insert(i);
        galaxy.push_back(bst);
    }
    init_dsu();
    int t, x, y;
    for (int i = 0; i < q; ++i) {
        std::cin >> t;
        if (t == 1) {
            std::cin >> x >> y;
            merge(x, y);
        } else {
            std::cin >> x;
            std::cout << galaxy[parent[x]].kthLargest(((galaxy[parent[x]].amount_nodes + 1) / 2)) << "\n";
        }
    }
}