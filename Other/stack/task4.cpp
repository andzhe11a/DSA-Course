#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

/*
* Да се реализира функция calculate, която приема математически израз
* под формата на низ (string) и връща неговия целочислен резултат.
* Изисквания:
* Операции: Поддръжка на събиране +, изваждане -, умножение *, деление / и степенуване ^.
* Приоритет: Спазване на математическия ред на действията
* (скоби -> унарни оператори -> степенуване -> умножение/деление -> събиране/изваждане).
* Степенуване: Операторът ^ е дясно-асоциативен (напр. 2^3^2 се смята като 2^(3^2)).
* Унарни оператори: Поддръжка на унарен плюс и минус (напр. -5 или (-5)).
* Валидация: Хвърляне на изключения при деление на нула, небалансирани скоби или невалиден синтаксис.
 */

struct Operator {
    char symbol;
    bool isUnary;
};

int getPrecedence(const Operator& op) {
    if (op.isUnary) return 4;
    if (op.symbol == '^') return 3;
    if (op.symbol == '*' || op.symbol == '/') return 2;
    if (op.symbol == '+' || op.symbol == '-') return 1;
    return 0;
}

int applyBinaryOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        case '^':
            return static_cast<int>(std::pow(a, b));
        default:
            throw std::runtime_error("Unknown binary operator");
    }
}

int applyUnaryOp(int a, char op) {
    switch (op) {
        case '-': return -a;
        case '+': return a;
        default:
            throw std::runtime_error("Unknown unary operator");
    }
}

void processTopOperation(std::stack<int>& values, std::stack<Operator>& ops) {
    if (ops.empty()) throw std::runtime_error("Invalid expression state");

    Operator op = ops.top();
    ops.pop();

    if (op.isUnary) {
        if (values.empty()) throw std::runtime_error("No operand for unary operator");

        int val = values.top();
        values.pop();

        values.push(applyUnaryOp(val, op.symbol));
    }
    else {
        if (values.size() < 2) throw std::runtime_error("Not enough operands for binary operator");

        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();

        values.push(applyBinaryOp(val1, val2, op.symbol));
    }
}

int calculate(const std::string& s) {
    std::stack<int> values;
    std::stack<Operator> ops;
    bool expectNum = true;

    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];

        if (std::isspace(c)) continue;

        if (std::isdigit(c)) {
            int val = 0;
            while (i < s.length() && std::isdigit(s[i])) {
                val = val * 10 + (s[i] - '0');
                i++;
            }
            values.push(val);
            i--;
            expectNum = false;
        }

        else if (c == '(') {
            ops.push({ '(', false });
            expectNum = true;
        }

        else if (c == ')') {
            while (!ops.empty() && ops.top().symbol != '(') {
                processTopOperation(values, ops);
            }
            if (ops.empty()) throw std::runtime_error("Unbalanced braces");
            ops.pop();
            expectNum = false;
        }

        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            Operator currentOp = { c, expectNum };

            if (currentOp.isUnary && c != '+' && c != '-') {
                throw std::runtime_error("Invalid unary operator");
            }

            while (!ops.empty() && ops.top().symbol != '(') {
                if (currentOp.symbol == '^' && ops.top().symbol == '^') {
                    break;
                }

                if (getPrecedence(ops.top()) < getPrecedence(currentOp)) {
                    break;
                }
                processTopOperation(values, ops);
            }
            ops.push(currentOp);
            expectNum = true;
        }

        else {
            throw std::runtime_error("Invalid character");
        }
    }

    while (!ops.empty()) {
        if (ops.top().symbol == '(') throw std::runtime_error("Unbalanced braces");
        processTopOperation(values, ops);
    }

    if (values.size() != 1) throw std::runtime_error("Invalid expression");

    return values.top();
}

int main() {
    std::string expr1 = "3 + 5 * ( 2 - 8 )";

    try {
        std::cout << "Test 1: " << expr1 << "\n";
        std::cout << "Result: " << calculate(expr1) << "\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    std::string expr2 = "2 ^ 3 ^ 2";

    try {
        std::cout << "Test 2: " << expr2 << "\n";
        std::cout << "Result: " << calculate(expr2) << "\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    std::string expr3 = "-5 + (-2 * 3)";

    try {
        std::cout << "Test 3: " << expr3 << "\n";
        std::cout << "Result: " << calculate(expr3) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}