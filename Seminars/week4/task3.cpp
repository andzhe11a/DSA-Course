#include <iostream>
#include <queue>
#include <string>

void generateBiaryNumbers(int n) {
    std::queue<std::string> q;

    q.push("1");

    for (size_t i = 0; i < n; i++) {
        std::string current = q.front();
        q.pop();

        std::cout << current << " ";

        q.push(current + "0");
        q.push(current + "1");
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;

    std::cout << "All binary numbers from 1 to " << n << ": " << std::endl;
    generateBiaryNumbers(n);

    return 0;
}