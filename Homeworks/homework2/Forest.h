#pragma once
#include <vector>
#include <string>
#include "AppleTree.h"

class Forest {
public:
    Forest();
    ~Forest();

    void addTree(const std::string& treeData);
    void addEdge(int u, int v, int weight);
    void solve();

private:
    std::vector<AppleTree*> trees;
    std::vector<std::vector<int>> adj;
    int totalPossibleApples;
};