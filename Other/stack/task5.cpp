#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

/*
* Да се напише функция, която приема string, представляващ математически израз,
* записан в обратен полски запис.
* Функцията трябва да изчислява стойността на израза или да съобщава за грешка при невалиден израз.
* Пример:
* evalReversePolish("345*-7+3/"); // (3 - 4 * 5 + 7) / 3 ==> -3
 */

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        default:
            throw std::invalid_argument("Invalid operator");
    }
}

int evalRPN(const std::string& s) {
    std::stack<int> values;

    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];

        if (std::isspace(c)) continue;

        if (std::isdigit(c)) {
            int val = 0;
            while (i < s.length() && std::isdigit(s[i])) {
                val = (val * 10) + (s[i] - '0');
                i++;
            }
            values.push(val);
            i--;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (values.size() < 2) {
                throw std::runtime_error("Not enough operands for operator");
            }

            int val2 = values.top(); values.pop();
            int val1 = values.top(); values.pop();

            values.push(applyOp(val1, val2, c));
        }
        else {
            throw std::runtime_error("Invalid character");
        }
    }

    if (values.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return values.top();
}

int main() {
    try {
        std::cout << evalRPN("3 4 5 * -") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}