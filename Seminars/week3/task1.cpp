#include <iostream>
#include <stack>

template <typename T>
void reverse(std::stack<T>& s) {
    std::stack<T> temp;

    while (!s.empty()) {
        temp.push(s.top());
        s.pop();
    }
    s = temp;
}

int main() {
    std::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    reverse(s);

    std::cout << "Stack: ";
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;

    return 0;
}