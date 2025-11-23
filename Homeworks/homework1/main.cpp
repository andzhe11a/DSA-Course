#include <iostream>
#include <string>
#include <queue>
#include "Token.h"
#include "Tokenizer.h"
#include "Parser.h"
#include "VariableStore.h"
#include "Expression.h"

void clearQueue(std::queue<Expression*>& q) {
    while (!q.empty()) {
        delete q.front();
        q.pop();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No command string provided!" << std::endl;
        return 1;
    }
    std::string commands = argv[1];

    VariableStore store;
    std::queue<Expression*> pendingQueue;
    int expressionCounter = 1;

    for (size_t i = 0; i < commands.length(); ++i) {
        char cmd = commands[i];

        if (cmd == 'R') {
            std::string line;
            if (!std::getline(std::cin, line) || line.empty()) {
                 break;
            }

            try {
                std::queue<Token> tokens = Tokenizer::tokenize(line.c_str());

                ParseResult res = Parser::parse(tokens);

                if (res.valid) {
                    Expression* expr = new Expression(expressionCounter, res.targetVar, res.rpnQueue);

                    delete[] res.targetVar;

                    pendingQueue.push(expr);
                    std::cout << "Expression (" << expressionCounter << ") was read." << std::endl;
                    expressionCounter++;
                } else {
                    delete[] res.targetVar;
                    std::cout << "Invalid syntax." << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
        else if (cmd == 'C') {
             if (pendingQueue.empty()) {
                continue;
            }

            Expression* current = pendingQueue.front();
            pendingQueue.pop();

            bool done = current->process(store);

            if (!done) {
                pendingQueue.push(current);
            } else {
                delete current;
            }
        }
        else {
            std::cerr << "Error: Invalid command '" << cmd << "' in command string!" << std::endl;
        }
    }

    if (!pendingQueue.empty()) {
        std::cout << "There are pending expressions. Do you want to try calculating them? (y/n): ";

        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            bool progressMade = true;
            while (progressMade && !pendingQueue.empty()) {
                progressMade = false;
                size_t qSize = pendingQueue.size();

                for (size_t i = 0; i < qSize; ++i) {
                    Expression* current = pendingQueue.front();
                    pendingQueue.pop();

                    bool done = current->process(store);

                    if (done) {
                        delete current;
                        progressMade = true;
                    } else {
                        pendingQueue.push(current);
                    }
                }
            }
            if (!pendingQueue.empty()) {
                std::cout << "Could not resolve remaining expressions." << std::endl;
            }
        }
    }

    clearQueue(pendingQueue);
    return 0;
}