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
std::vector<T> vectorUnion(const std::vector<T>& first, const std::vector<T>& second) {
    std::vector<T> result;
    result.reserve(first.size() + second.size());

    for (size_t i = 0; i < first.size(); ++i) {
        if (!isAlreadyPresent(result, first[i])) {
            result.push_back(first[i]);
        }
    }

    for (size_t i = 0; i < second.size(); ++i) {
        if (!isAlreadyPresent(result, second[i])) {
            result.push_back(second[i]);
        }
    }

    return result;
}

int main() {
    std::vector<int> first = {1, 2, 8, 2, 5};
    std::vector<int> second = {5, 3, 9, 10, 3};

    std::vector<int> united = vectorUnion(first, second);
    std::cout << "United: ";
    for (size_t i = 0; i < united.size(); ++i) {
        std::cout << united[i] << " ";
    }
    std::cout << "\n";

    return 0;
}