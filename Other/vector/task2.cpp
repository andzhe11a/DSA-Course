#include <iostream>
#include <vector>
#include <string>

/*
 * Създайте програма, която прочита символен низ от стандартния вход
 * и извежда на стандартния изход хистограма за английската азбука.
 * Приемете, че символния низ съдържа само латински букви, малки и големи.
 */

int main() {
    std::string input;
    std::getline(std::cin, input);

    std::vector<int> occurances(26, 0);

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        if (std::isalpha(c)) {
            char curr = std::toupper(c);
            int letterIndex = curr - 'A';

            occurances[letterIndex]++;
        }
    }

    for (size_t i = 0; i < occurances.size(); ++i) {
        char currLetter = i + 'A';
        std::cout << currLetter << ": ";

        for (int j = 0; j < occurances[i]; ++j) {
            std::cout << "*";
        }

        std::cout << std::endl;
    }

    return 0;
}