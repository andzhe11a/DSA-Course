#include <iostream>
#include <stack>

class Queue {
    std::stack<int> input, output;
public:
    void push(const int x) {
        input.push(x);
    }

    void pop(void) {
        peek();
        output.pop();
    }

    int peek(void) {
        if (output.empty())
            while (input.size())
                output.push(input.top()), input.pop();
        return output.top();
    }

    bool empty(void) const {
        return input.empty() && output.empty();
    }
};