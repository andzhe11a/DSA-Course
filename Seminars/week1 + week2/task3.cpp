#include <iostream>
#include <vector>

template <typename T>
bool isAlreadyPresent(const std::vector<T>& vec, const T& element) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == element) {
            return true;
        }
    }
    return false;
}

template <typename T>
std::vector<T> intersection(const std::vector<T>& first, const std::vector<T>& second) {
    std::vector<T> result;
    size_t smallerSize = (first.size() < second.size()) ? first.size() : second.size();
    result.reserve(smallerSize);

    for (size_t i = 0; i < first.size(); ++i) {
        const T& candidate = first[i];
        bool presentInSecond = false;

        for (size_t j = 0; j < second.size(); ++j) {
            if (candidate == second[j]) {
                presentInSecond = true;
                break;
            }
        }
        if (presentInSecond && !isAlreadyPresent(result, candidate)) {
            result.push_back(candidate);
        }
    }
    return result;
}

int main() {
    std::vector<int> first = {1, 5, 10, 2, 5};
    std::vector<int> second = {10, 3, 5, 1, 3};

    std::vector<int> intersected = intersection(first, second);
    std::cout << "Intersected: ";
    for (size_t i = 0; i < intersected.size(); ++i) {
        std::cout << intersected[i] << " ";
    }
    std::cout << "\n";

    return 0;
}