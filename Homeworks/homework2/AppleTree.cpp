#include "AppleTree.h"
#include <algorithm>

AppleTree::AppleTree(const std::string& data) : root(nullptr) {
    int pos = 0;
    if (data.empty()) return;

    root = parse(data, pos);
}

AppleTree::~AppleTree() {
    clear(root);
}

void AppleTree::clear(const Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void AppleTree::skipSpaces(const std::string& str, int& pos) {
    while (pos < str.length() && std::isspace(str[pos])) {
        pos++;
    }
}

AppleTree::Node* AppleTree::parse(const std::string& str, int& pos) {
    skipSpaces(str, pos);

    if (pos >= str.length()) return nullptr;

    if (str[pos] == 'x' || str[pos] == 'X') {
        pos++;
        return nullptr;
    }

    if (str[pos] == '(') {
        pos++;
        skipSpaces(str, pos);

        int apples = 0;
        while (pos < str.length() && std::isdigit(str[pos])) {
            apples = apples * 10 + (str[pos] - '0');
            pos++;
        }

        Node* node = new Node(apples);

        try {
            node->left = parse(str, pos);
            node->right = parse(str, pos);

            skipSpaces(str, pos);

            if (pos < str.length() && str[pos] == ')') {
                pos++;
            } else {
                throw std::runtime_error("Missing closing parenthesis");
            }
        }
        catch (...) {
            clear(node);
            throw;
        }
        return node;
    }
    throw std::runtime_error("Invalid character in tree definition");
}

int AppleTree::collectApples() const {
    return collectApplesHelper(root);
}

int AppleTree::collectApplesHelper(const Node* node) const {
    if (!node) return 0;

    int currentApple = (node->apples > 0) ? 1 : 0;

    return currentApple + collectApplesHelper(node->left) + collectApplesHelper(node->right);
}

int AppleTree::calculateTime() const {
    int h = getHeight(root);

    return h * 2;
}

int AppleTree::getHeight(const Node* node) const {
    if (!node) return 0;

    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}