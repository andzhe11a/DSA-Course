#include <iostream>
#include <string>
#include "Forest.h"

int main() {
    try {
        int numTrees, numPaths;

        if (!(std::cin >> numTrees >> numPaths)) {
            return 0;
        }

        if (numTrees < 0 || numPaths < 0) {
            throw std::runtime_error("Number of trees or paths cannot be negative");
        }

        std::cin.ignore();

        Forest forest;

        for (int i = 0; i < numTrees; ++i) {
            std::string line;
            while (std::getline(std::cin, line)) {
                if (!line.empty()) {
                    break;
                }
            }

            if (line.empty()) {
                throw std::runtime_error("Unexpected end of input");
            }
            forest.addTree(line);
        }

        for (int i = 0; i < numPaths; ++i) {
            int u, v, w;
            if (!(std::cin >> u >> v >> w)) {
                throw std::runtime_error("Invalid path input");
            }
            forest.addEdge(u, v, w);
        }
        forest.solve();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
    return 0;
}