#include <iostream>
#include <vector>

template <typename T>
std::vector<T> append(const std::vector<T>& first, const std::vector<T>& second) {
    size_t totalSize = first.size() + second.size();

    std::vector<T> result;
    result.reserve(totalSize);

    result.insert(result.end(), first.begin(), first.end());
    result.insert(result.end(), second.begin(), second.end());

    return result;
}

int main() {
    std::vector<int> first = {1, 2, 3};
    std::vector<int> second = {4, 5, 6};

    std::vector<int> appended = append(first, second);
    std::cout << "Appended: ";
    for (size_t i = 0; i < appended.size(); ++i) {
        std::cout << appended[i] << " ";
    }
    std::cout << "\n";

    return 0;
}