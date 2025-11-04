#include <iostream>
#include <stack>
#include <string>

class Solution {
public:
    int scoreOfParentheses(const std::string& s) {
        std::stack<int> parentScoresStack;
        int currentScore = 0;

        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                parentScoresStack.push(currentScore);
                currentScore = 0;
            }
            else {
                currentScore = parentScoresStack.top() + std::max(2 * currentScore, 1);
                parentScoresStack.pop();
            }
        }
        return currentScore;
    }
};