#include "Forest.h"
#include <iostream>
#include <queue>

Forest::Forest() : totalPossibleApples(0) {}

Forest::~Forest() {
    for (int i = 0; i < trees.size(); ++i) {
        delete trees[i];
    }
}

void Forest::addTree(const std::string& treeData) {
    AppleTree* newTree = new AppleTree(treeData);

    try {
        trees.push_back(newTree);
        adj.resize(trees.size());
        totalPossibleApples += newTree->collectApples();
    }
    catch (...) {
        delete newTree;
        if (trees.size() > adj.size()) {
            trees.pop_back();
        }
        throw;
    }
}

void Forest::addEdge(int u, int v, int weight) {
    if (u >= 0 && u < trees.size() && v >= 0 && v < trees.size()) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void Forest::solve() {
    if (trees.empty()) {
        std::cout << "0 0" << std::endl;
        return;
    }

    int n = trees.size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;

    q.push(0);
    visited[0] = true;

    int collectedApples = 0;
    int totalTime = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        collectedApples += trees[current]->collectApples();
        totalTime += trees[current]->calculateTime();

        for (int i = 0; i < adj[current].size(); ++i) {
            int neighbor = adj[current][i];

            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    std::cout << collectedApples << " " << totalTime << std::endl;

    if (collectedApples < totalPossibleApples) {
        std::cout << "Unreachable apples detected!" << std::endl;
    }
}