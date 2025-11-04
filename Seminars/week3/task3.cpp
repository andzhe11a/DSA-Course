#include <iostream>
#include <stack>
#include <vector>

class Solution {
public:
    bool validateStackSequences(const std::vector<int>& pushed, const std::vector<int>& popped) {
        std::stack<int> stack;
        size_t poppedIndex = 0;

        for (size_t pushedIndex = 0; pushedIndex < pushed.size(); ++pushedIndex) {
            stack.push(pushed[pushedIndex]);

            while (!stack.empty() && stack.top() == popped[poppedIndex]) {
                stack.pop();
                poppedIndex++;
            }
        }
        return stack.empty();
    }
};