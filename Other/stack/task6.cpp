#include <iostream>
#include <stack>
#include <string>

/*
* Ще дефинираме свойството симетричност за string както следва:
* Празният string е симетричен
* Ако str е симетричен, ch1 е малка буква и ch2 е съответстващата й главна буква (пр: 'A' съответства на 'a'),
* то ch1 . str . ch2 е симетричен
* Ако str1 и str2 са симетрични, то str1 . str2 е симетричен
* (Забележка: Със знак ' . ' бележим операцията конкатенация на string-ове.)
* Да се напише функция, която приема string и проверява дали той е симетричен.
* Приемете, че няма да получите string със символи, различни от малки и главни букви.
Пример:
isSymmetric("qweEWQrtTR"); // -> true
isSymmetric("AaBbCc"); // -> false
*/

bool isSymmetric(const std::string& str) {
    std::stack<char> s;

    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];

        if (islower(c)) {
            s.push(c);
        }
        else if (isupper(c)) {
            if (s.empty()) return false;

            char expectedSmall = s.top();

            if (expectedSmall != tolower(c)) return false;

            s.pop();
        }
    }
    return s.empty();
}

int main()
{
    std::cout << std::boolalpha << isSymmetric("qweEWQrtTR") << std::endl;
    std::cout << isSymmetric("AaBbCc");
}