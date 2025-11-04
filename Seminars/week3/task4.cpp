#include <iostream>
#include <stack>
#include <vector>

class Solution {
public:
    std::vector<int> asteroidCollision(const std::vector<int>& asteroids) {
        std::stack<int> unexplodedStack;
        for (size_t i = 0; i < asteroids.size(); ++i) {
            int currAsteroid = asteroids[i];

            if (currAsteroid > 0) {
                unexplodedStack.push(currAsteroid);
            }
            else {
                while (!unexplodedStack.empty() && unexplodedStack.top() > 0 && unexplodedStack.top() < -currAsteroid) {
                    unexplodedStack.pop();
                }
                if (unexplodedStack.empty() || unexplodedStack.top() < 0) {
                    unexplodedStack.push(currAsteroid);
                }
                else if (unexplodedStack.top() == -currAsteroid) {
                    unexplodedStack.pop();
                }
            }
        }
        std::vector<int> result(unexplodedStack.size());
        size_t index = unexplodedStack.size();

        while (!unexplodedStack.empty()) {
            result[--index] = unexplodedStack.top();
            unexplodedStack.pop();
        }
        return result;
    }
};