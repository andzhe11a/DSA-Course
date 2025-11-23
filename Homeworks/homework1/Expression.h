#pragma once
#include "Token.h"
#include "VariableStore.h"
#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>

char toUpperExpr(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }
    return c;
}

bool areExprEqual(const char* s1, const char* s2) {
    if (!s1 || !s2) {
        return false;
    }
    while (*s1 && *s2) {
        if (toUpperExpr(*s1) != toUpperExpr(*s2)) {
            return false;
        }
        s1++; s2++;
    }
    return *s1 == *s2;
}

class Expression {
public:
    Expression(int i, const char* var, const std::queue<Token>& rpn)
        : id(i), rpnQueue(rpn) {
        if (var) {
            targetVar = new char[std::strlen(var) + 1];
            std::strcpy(targetVar, var);
        } else {
            targetVar = nullptr;
        }
    }

    ~Expression() {
        delete[] targetVar;
    }

    int getId() const { return id; }

    bool process(VariableStore& store) {
        std::stack<std::queue<Token>> evalStack;
        std::queue<Token> input = rpnQueue;

        while (!input.empty()) {
            Token t = input.front();
            input.pop();

            if (t.type == TOKEN_NUMBER) {
                std::queue<Token> q;
                q.push(t);
                evalStack.push(q);
            }
            else if (t.type == TOKEN_VARIABLE) {
                double val;
                if (t.text == nullptr) {
                    throw std::runtime_error("Variable token has no name!");
                }
                char symbol = t.text[0];
                std::queue<Token> q;

                if (store.getValue(symbol, val)) {
                    q.push(Token(TOKEN_NUMBER, nullptr, val));
                } else {
                    q.push(t);
                }
                evalStack.push(q);
            }
            else if (t.isUnary) {
                if (evalStack.empty()) {
                    std::cout << "Invalid expression (missing operand for unary)." << std::endl;
                    return true;
                }
                std::queue<Token> operand = evalStack.top();
                evalStack.pop();

                if (operand.size() == 1 && operand.front().type == TOKEN_NUMBER) {
                    double v = operand.front().value;
                    if (t.text && t.text[0] == '-') {
                        v = -v;
                    }

                    std::queue<Token> res;
                    res.push(Token(TOKEN_NUMBER, nullptr, v));
                    evalStack.push(res);
                } else {
                    operand.push(t);
                    evalStack.push(operand);
                }
            }
            else if (t.type == TOKEN_OPERATOR) {
                if (t.text == nullptr) throw std::runtime_error("Operator text missing!");
                char op = t.text[0];

                if (evalStack.size() < 2) {
                    std::cout << "Invalid expression (missing operands)." << std::endl;
                    return true;
                }
                std::queue<Token> right = evalStack.top();
                evalStack.pop();
                std::queue<Token> left = evalStack.top();
                evalStack.pop();

                if (right.size() == 1 && right.front().type == TOKEN_NUMBER &&
                    left.size() == 1 && left.front().type == TOKEN_NUMBER) {

                    double rVal = right.front().value;
                    double lVal = left.front().value;
                    double resVal = 0;

                    if (op == '+') {
                        resVal = lVal + rVal;
                    } else if (op == '-') {
                        resVal = lVal - rVal;
                    } else if (op == '*') {
                        resVal = lVal * rVal;
                    } else if (op == '/') {
                        if (rVal == 0) {
                            std::cout << "Error: Division by zero." << std::endl;
                            return true;
                        }
                        resVal = lVal / rVal;
                    } else if (op == '^') {
                        resVal = std::pow(lVal, rVal);
                    }

                    std::queue<Token> resQ;
                    resQ.push(Token(TOKEN_NUMBER, nullptr, resVal));
                    evalStack.push(resQ);
                    } else {
                        while (!right.empty()) {
                            left.push(right.front());
                            right.pop();
                        }
                        left.push(t);
                        evalStack.push(left);
                    }
            }
            else if (t.type == TOKEN_FUNCTION) {
                size_t count = t.argCount;
                if (evalStack.size() < count) {
                    std::cout << "Invalid expression (function args mismatch)." << std::endl;
                    return true;
                }

                std::stack<std::queue<Token>> argsReversed;
                for (int i = 0; i < count; ++i) {
                    argsReversed.push(evalStack.top());
                    evalStack.pop();
                }

                bool allNumbers = true;
                std::queue<double> values;
                std::queue<Token> combinedArgs;

                while(!argsReversed.empty()) {
                    std::queue<Token> arg = argsReversed.top();
                    argsReversed.pop();

                    if (arg.size() == 1 && arg.front().type == TOKEN_NUMBER) {
                        values.push(arg.front().value);
                    } else {
                        allNumbers = false;
                    }

                    while (!arg.empty()) {
                        combinedArgs.push(arg.front());
                        arg.pop();
                    }
                }

                if (allNumbers) {
                    double resVal = calculateFunc(t.text, values);
                    std::queue<Token> resQ;
                    resQ.push(Token(TOKEN_NUMBER, nullptr, resVal));
                    evalStack.push(resQ);
                } else {
                    combinedArgs.push(t);
                    evalStack.push(combinedArgs);
                }
            }
        }

        if (evalStack.size() == 1) {
            std::queue<Token>& finalResult = evalStack.top();

            if (finalResult.size() == 1 && finalResult.front().type == TOKEN_NUMBER) {
                double val = finalResult.front().value;

                if (targetVar) {
                    store.setValue(targetVar[0], val);
                }

                std::cout << "Expression (" << id << ") was calculated.";
                if (targetVar) {
                    std::cout << " The value of " << targetVar << " is now " << val << ".";
                } else {
                    std::cout << " Result: " << val;
                }
                std::cout << std::endl;

                evalStack.pop();
                return true;
            } else {
                rpnQueue = finalResult;
                evalStack.pop();
                std::cout << "Expression (" << id << ") was postponed." << std::endl;
                return false;
            }
        } else {
            std::cout << "Invalid expression format." << std::endl;
            return true;
        }
    }

private:
    int id;
    char* targetVar;
    std::queue<Token> rpnQueue;

    static double calculateFunc(const char* name, std::queue<double>& vals) {
        if (vals.empty()) {
            throw std::runtime_error("Function cannot be called with no arguments!");
        }
        if (name == nullptr) {
            return 0;
        }

        if (areExprEqual(name, "SUM")) {
            double s = 0;
            while(!vals.empty()) { s += vals.front(); vals.pop(); }
            return s;
        }
        if (areExprEqual(name, "PRD")) {
            double p = 1;
            while(!vals.empty()) { p *= vals.front(); vals.pop(); }
            return p;
        }
        if (areExprEqual(name, "AVG")) {
            double s = 0;
            size_t c = vals.size();
            if (c == 0) {
                return 0;
            }
            while(!vals.empty()) {
                s += vals.front(); vals.pop();
            }
            return s / c;
        }
        if (areExprEqual(name, "MIN")) {
            double m = vals.front(); vals.pop();
            while(!vals.empty()) {
                if (vals.front() < m) {
                    m = vals.front();
                }
                vals.pop();
            }
            return m;
        }
        if (areExprEqual(name, "MAX")) {
            double m = vals.front(); vals.pop();
            while(!vals.empty()) {
                if (vals.front() > m) {
                    m = vals.front();
                }
                vals.pop();
            }
            return m;
        }
        return 0;
    }
};