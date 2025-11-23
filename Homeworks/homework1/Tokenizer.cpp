#include "Tokenizer.h"
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <cstdlib>

char toUpperToken(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }
    return c;
}

bool areStrEqual(const char* s1, const char* s2) {
    if (!s1 || !s2) {
        return false;
    }
    while (*s1 && *s2) {
        if (toUpperToken(*s1) != toUpperToken(*s2)) {
            return false;
        }
        s1++;
        s2++;
    }
    return *s1 == *s2;
}

std::queue<Token> Tokenizer::tokenize(const char* expression) {
    std::queue<Token> tokens;
    size_t i = 0;
    size_t len = std::strlen(expression);
    bool expectingOperand = true;

    while (i < len) {
        char c = expression[i];

        if (isSpace(c)) {
            i++;
            continue;
        }

        if (isDigit(c) || c == '.') {
            size_t start = i;
            i++;
            while (i < len && (isDigit(expression[i]) || expression[i] == '.')) {
                i++;
            }

            size_t numLen = i - start;
            char* buffer = new char[numLen + 1];
            std::strncpy(buffer, expression + start, numLen);
            buffer[numLen] = '\0';

            tokens.push(Token(TOKEN_NUMBER, buffer, std::atof(buffer)));
            delete[] buffer;
            expectingOperand = false;
        }
        else if (isLetter(c)) {
            size_t start = i;
            while (i < len && isLetter(expression[i])) {
                i++;
            }
            size_t nameLen = i - start;
            char* buffer = new char[nameLen + 1];
            std::strncpy(buffer, expression + start, nameLen);
            buffer[nameLen] = '\0';

            if (nameLen == 1) {
                tokens.push(Token(TOKEN_VARIABLE, buffer));
                expectingOperand = false;
            }
            else {
                bool isFunc = false;
                const char* funcs[] = {"SUM", "MIN", "MAX", "AVG", "PRD"};

                for (int k = 0; k < 5; ++k) {
                    if (areStrEqual(buffer, funcs[k])) {
                        isFunc = true;
                        break;
                    }
                }
                if (isFunc) {
                    tokens.push(Token(TOKEN_FUNCTION, buffer));
                    expectingOperand = true;
                } else {
                    delete[] buffer;

                    throw std::runtime_error("Unknown identifier (variables must be 1 char).");
                }
            }
            delete[] buffer;
        }
        else {
            char temp[2] = {c, '\0'};
            if (c == '(') {
                tokens.push(Token(TOKEN_LPAREN, temp));
                expectingOperand = true;
            }
            else if (c == ')') {
                tokens.push(Token(TOKEN_RPAREN, temp));
                expectingOperand = false;
            }
            else if (c == ';') {
                tokens.push(Token(TOKEN_COMMA, temp));
                expectingOperand = true;
            }
            else if (c == '=') {
                tokens.push(Token(TOKEN_ASSIGN, temp));
                expectingOperand = true;
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                bool isUnary = false;
                if (expectingOperand && (c == '+' || c == '-')) {
                    isUnary = true;
                }
                tokens.push(Token(TOKEN_OPERATOR, temp, 0.0, isUnary));
                expectingOperand = true;
            }
            else {
                std::cerr << "Invalid symbol!" << std::endl;
            }
            i++;
        }
    }
    return tokens;
}