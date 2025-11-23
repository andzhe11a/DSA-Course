#pragma once
#include "Token.h"
#include <queue>

class Tokenizer {
public:
    static std::queue<Token> tokenize(const char* expression);

private:
    static bool isDigit(const char c) { return (c >= '0' && c <= '9'); }
    static bool isLetter(const char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
    static bool isSpace(const char c) { return c == ' ' || c == '\t' || c == '\n'; }
};