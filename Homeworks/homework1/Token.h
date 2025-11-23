#pragma once
#include <cstring>

enum TokenType {
    TOKEN_NUMBER,
    TOKEN_VARIABLE,
    TOKEN_OPERATOR,
    TOKEN_FUNCTION,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_COMMA,
    TOKEN_ASSIGN
};

struct Token {
    TokenType type;
    char* text;
    double value;
    bool isUnary;
    int argCount;

    Token() : type(TOKEN_NUMBER), text(nullptr), value(0), isUnary(false), argCount(0) {}

    Token(TokenType t, const char* txt, double val = 0.0, bool unary = false, int args = 0)
        : type(t), value(val), isUnary(unary), argCount(args) {
        if (txt) {
            text = new char[std::strlen(txt) + 1];
            std::strcpy(text, txt);
        } else {
            text = nullptr;
        }
    }

    Token(const Token& other)
        : type(other.type), value(other.value), isUnary(other.isUnary), argCount(other.argCount) {
        if (other.text) {
            text = new char[std::strlen(other.text) + 1];
            std::strcpy(text, other.text);
        } else {
            text = nullptr;
        }
    }

    Token& operator=(const Token& other) {
        if (this != &other) {
            delete[] text;
            type = other.type;
            value = other.value;
            isUnary = other.isUnary;
            argCount = other.argCount;

            if (other.text) {
                text = new char[std::strlen(other.text) + 1];
                std::strcpy(text, other.text);
            } else {
                text = nullptr;
            }
        }
        return *this;
    }

    ~Token() {
        delete[] text;
    }

    int getPriority() const {
        if (type != TOKEN_OPERATOR) return 0;
        if (isUnary) return 4;
        if (text && std::strcmp(text, "^") == 0) return 3;
        if (text && (std::strcmp(text, "*") == 0 || std::strcmp(text, "/") == 0)) return 2;
        if (text && (std::strcmp(text, "+") == 0 || std::strcmp(text, "-") == 0)) return 1;
        return 0;
    }

    bool isRightAssociative() const {
        return (text && std::strcmp(text, "^") == 0) || isUnary;
    }
};