#include <iostream>
#include <stack>
#include <string>

/*
* Автентикирайте израз, съдържащ само скоби. Всяка скоба трябва да има съответстваща затваряща скоба
Valid Parentheses {EASY}
Пример:
[({)}] → Невалиден
[({})] → Валиден
 */

bool isValid(const std::string& str) {
    std::stack<char> brackets;

    for (char ch : str) {
        if (ch == '(' || ch == '{' || ch == '[') {
            brackets.push(ch);
        }
        else {
            if (brackets.empty()) {
                return false;
            }

            char lastOpenBracket = brackets.top();

            bool isMatching = (ch == ')' && lastOpenBracket == '(' ||
                               ch == '}' && lastOpenBracket == '{' ||
                               ch == ']' && lastOpenBracket == '[');

            if (isMatching) {
                brackets.pop();
            }
            else {
                return false;
            }
        }
    }

    return brackets.empty();
}

int main() {
    std::string test1 = "[({})]";
    std::string test2 = "[({)}]";
    std::string test3 = "(()";

    std::cout << test1 << " -> " << (isValid(test1) ? "Valid" : "Invalid") << std::endl;
    std::cout << test2 << " -> " << (isValid(test2) ? "Valid" : "Invalid") << std::endl;
    std::cout << test3 << " -> " << (isValid(test3) ? "Valid" : "Invalid") << std::endl;

    return 0;
}