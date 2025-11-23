#pragma once
#include "Token.h"
#include <queue>

struct ParseResult {
    char* targetVar;
    std::queue<Token> rpnQueue;
    bool valid;

    ParseResult() : targetVar(nullptr), valid(false) {}
};

class Parser {
public:
    static ParseResult parse(std::queue<Token>& tokens);
};