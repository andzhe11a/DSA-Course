#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

/*
 * Изчислете стойността на израз. Валидни операции сa +, -, *, /,
 * като приоритетът им е следният:*, / > +, -.
 * В изразът могат да се срещат и единични скоби (,).
 * При такъв случай всичко в скобите е с по висок приоритет от другите операции.
 */

int getPrecedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int applyOp(int a, int b, char op)
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        default:
            throw std::runtime_error("Invalid operator");
    }
}

int calculate(const std::string& str) {
    std::stack<int> values;
    std::stack<char> ops;

    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];

        if (c == ' ') continue;

        if (isdigit(c)) {
            int val = 0;
            while (i < str.length() && std::isdigit(str[i])) {
                val = (val * 10) + (str[i] - '0');
                i++;
            }
            values.push(val);
            i--;
        }

        else if (c == '(') {
            ops.push(c);
        }

        else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty()) {
                ops.pop();
            }
        }

        else {
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(c)) {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }
            ops.push(c);
        }
    }
    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();
        int val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

int main() {
    std::string str = "3 + 5 * ( 2 - 8 )";

    std::cout << "Expression: " << str << std::endl;
    std::cout << "Result: " << calculate(str) << std::endl;

    return 0;
}