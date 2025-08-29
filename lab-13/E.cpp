#include <iostream>
#include <string>
#include <map>

class LibraryTree {
public:
    void Insert(const std::string& author) {
        root = insert(root, author);
    }

    std::string kthAuthor(int k) {
        Node* x = jump_traverse(root, k, 0);
        if (x!= nullptr) {
            return x->author;
        } else {
            return "";
        }
    }

private:
    struct Node {
        Node *left_child;
        Node *right_child;
        std::string author;
        int element_count;

        Node(const std::string& Author) : left_child(nullptr), right_child(nullptr), author(Author), element_count(1) {}
    };

    Node *root = nullptr;

    void AmountFactor(Node* temp_node) {
        int left_amount;
        int right_amount;
        if (temp_node->left_child!= nullptr) {
            left_amount = temp_node->left_child->element_count;
        } else {
            left_amount = 0;
        }
        if (temp_node->right_child!= nullptr) {
            right_amount = temp_node->right_child->element_count;
        } else {
            right_amount = 0;
        }
        temp_node->element_count = left_amount + right_amount + 1;
    }

    Node *insert(Node *future_parent, const std::string& author) {
        if (future_parent == nullptr) {
            return new Node(author);
        } else if (author > future_parent->author) {
            future_parent->left_child = insert(future_parent->left_child, author);
        } else if (author <= future_parent->author) {
            future_parent->right_child = insert(future_parent->right_child, author);
        }
        AmountFactor(future_parent);
        return future_parent;
    }

    Node *jump_traverse(Node* temp_node, const int& k, int visited) {
        int r;
        if (temp_node->right_child == nullptr) {
            r = 0;
        } else {
            r = (temp_node->right_child)->element_count;
        }
        if ((visited + r >= k) && (temp_node->right_child!= nullptr)) {
            return jump_traverse(temp_node->right_child, k, visited);
        } else if (visited + r == k - 1) {
            return temp_node;
        } else if ((visited + r < k - 1) && (temp_node->left_child!= nullptr)) {
            return jump_traverse(temp_node->left_child, k, visited + r + 1);
        }
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    LibraryTree library;
    int N;
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        std::string author;
        std::cin >> author;
        if (std::isdigit(author[0])) {
            int k = std::stoi(author);
            std::cout << library.kthAuthor(k) << std::endl;
        } else {
            library.Insert(author);
        }
    }
    return 0;
}
