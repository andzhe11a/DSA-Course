#pragma once
#include <string>

class AppleTree {
public:
    AppleTree(const std::string& data);
    ~AppleTree();

    int collectApples() const;
    int calculateTime() const;

private:
    struct Node {
        int apples;
        Node* left;
        Node* right;

        Node(int val) : apples(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* parse(const std::string& str, int& pos);
    void clear(const Node* node);
    int collectApplesHelper(const Node* node) const;
    int getHeight(const Node* node) const;
    void skipSpaces(const std::string& str, int& pos);
};