#include "Parser.h"
#include <iostream>
#include <cstring>

ParseResult Parser::parse(std::queue<Token>& tokens) {
    ParseResult result;
    if (tokens.empty()) {
        return result;
    }

    Token firstToken = tokens.front();
    tokens.pop();
    bool isAssignment = false;

    if (!tokens.empty() && tokens.front().type == TOKEN_ASSIGN) {
        isAssignment = true;
        if (firstToken.type == TOKEN_VARIABLE) {
            if (firstToken.text) {
                result.targetVar = new char[std::strlen(firstToken.text) + 1];
                std::strcpy(result.targetVar, firstToken.text);
            } else {
                result.targetVar = nullptr;
            }
            tokens.pop();
        } else {
            std::cerr << "Assignment must start with a variable." << std::endl;
            return result;
        }
    }

    std::queue<Token> outputQueue;
    std::stack<Token> opStack;
    std::stack<int> argCounts;

    if (!isAssignment) {
        if (firstToken.type == TOKEN_NUMBER || firstToken.type == TOKEN_VARIABLE) {
            outputQueue.push(firstToken);
        }
        else if (firstToken.type == TOKEN_LPAREN) {
            opStack.push(firstToken);
            argCounts.push(0);
        }
        else if (firstToken.type == TOKEN_FUNCTION || firstToken.type == TOKEN_OPERATOR) {
            opStack.push(firstToken);
        }
    }

    while (!tokens.empty()) {
        Token t = tokens.front();
        tokens.pop();

        if (t.type == TOKEN_NUMBER || t.type == TOKEN_VARIABLE) {
            outputQueue.push(t);
        }
        else if (t.type == TOKEN_FUNCTION) {
            opStack.push(t);
        }
        else if (t.type == TOKEN_LPAREN) {
            if (!opStack.empty() && opStack.top().type == TOKEN_FUNCTION) {
                if (!tokens.empty() && tokens.front().type == TOKEN_RPAREN) {
                    argCounts.push(0);
                } else {
                    argCounts.push(1);
                }
            } else {
                argCounts.push(0);
            }
            opStack.push(t);
        }
        else if (t.type == TOKEN_COMMA) {
            while (!opStack.empty() && opStack.top().type != TOKEN_LPAREN) {
                outputQueue.push(opStack.top());
                opStack.pop();
            }
            if (!argCounts.empty()) {
                int c = argCounts.top();
                argCounts.pop();
                argCounts.push(c + 1);
            }
        }
        else if (t.type == TOKEN_RPAREN) {
            while (!opStack.empty() && opStack.top().type != TOKEN_LPAREN) {
                outputQueue.push(opStack.top());
                opStack.pop();
            }

            if (!opStack.empty()) {
                opStack.pop();
            }

            if (!opStack.empty() && opStack.top().type == TOKEN_FUNCTION) {
                Token funcToken = opStack.top();
                opStack.pop();

                int count = 0;
                if (!argCounts.empty()) {
                    count = argCounts.top();
                    argCounts.pop();
                }

                funcToken.argCount = count;

                outputQueue.push(funcToken);
            } else {
                if (!argCounts.empty()) {
                    argCounts.pop();
                }
            }
        }
        else if (t.type == TOKEN_OPERATOR) {
            while (!opStack.empty() && opStack.top().type != TOKEN_LPAREN) {
                Token top = opStack.top();
                if (top.getPriority() > t.getPriority() ||
                   (top.getPriority() == t.getPriority() && !t.isRightAssociative())) {
                    outputQueue.push(top);
                    opStack.pop();
                } else {
                    break;
                }
            }
            opStack.push(t);
        }
    }

    while (!opStack.empty()) {
        if (opStack.top().type == TOKEN_LPAREN) {
            std::cerr << "Mismatched parentheses." << std::endl;
            return result;
        }
        outputQueue.push(opStack.top());
        opStack.pop();
    }

    result.rpnQueue = outputQueue;
    result.valid = true;
    return result;
}