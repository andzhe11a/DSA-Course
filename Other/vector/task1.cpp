#include <iostream>
#include <vector>

/* Създайте програма, която прочита от стандартния вход размер на масив N.
 Специален елемент наричаме такъв елемент, че сумата на всички елементи преди него
 е равна на сумата на всички елементи след него.
 Приемете, че в масива съществува точно един такъв елемент.
 На стандартния изход изведете индекса на този елемент, ако съществува.*/

int main() {
    int N;
    if (!(std::cin >> N)) return 0;

    std::vector<int> arr(N);
    int totalSum = 0;

    for (size_t i = 0; i < N; ++i) {
        std::cin >> arr[i];
        totalSum += arr[i];
    }

    int leftSum = 0;

    for (size_t i = 0; i < N; ++i) {
        int rightSum = totalSum - leftSum - arr[i];

        if (rightSum == leftSum) {
            std::cout << i << std::endl;
        }

        leftSum += arr[i];
    }

    return 0;
}