#include <iostream>
#include <stack>
#include <string>

/*Превърнете израз от инфиксна нотация в постфиксна (RPN)
Пример:
Вход: 3 + 4 * 2 / 1 - 5
Изход: 3 4 2 * 1 / + 5 -          */

int getPrecedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infixToRPN(const std::string& str) {
    std::stack<char> s;

    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];

        if (c == ' ') continue;

        if (std::isdigit(c)) {
            std::cout << c << " ";
        }
        else if (c == '(') {
            s.push(c);
        }
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                std::cout << s.top() << " ";
                s.pop();
            }
        }
        else {
            while (!s.empty() && getPrecedence(s.top()) >= getPrecedence(c)) {
                std::cout << s.top() << " ";
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

int main() {
    std::string input = "3 + 4 * 2 / 1 - 5";

    std::cout << "Infix:   " << input << std::endl;
    std::cout << "Postfix: ";
    infixToRPN(input);

    return 0;
}