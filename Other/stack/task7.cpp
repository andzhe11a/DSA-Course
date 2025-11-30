#include <iostream>
#include <stack>
#include <string>

// Valid Parentheses

bool isValid(const std::string& str) {
    std::stack<char> s;

    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];

        if (c == '(' || c == '{' || c == '[') {
            s.push(c);
        } else if (c == ')' || c == '}' || c ==']') {
            if (s.empty()) return false;
            char topBracket = s.top();

            bool isMatching (c == ')' && topBracket == '(' ||
                c == '}' && topBracket == '{' ||
                c == ']' && topBracket == '[');

            if (isMatching) s.pop();
            else return false;
        }
        else throw;
    }
    return s.empty();
}

int main()
{
    std::cout << std::boolalpha << isValid("[({})]") << std::endl;
    std::cout << isValid("[({)}]");
}