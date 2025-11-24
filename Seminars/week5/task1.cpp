#include <iostream>

template <typename T>
struct Node {
    T value;
    Node* next;

    Node(const T& value = T(), Node* next = nullptr)
        : value(value), next(next) {}


    ~Node() {
        delete next;
    }

    void add(T value) {
        Node* current = this;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = new Node(value);
    }
};

template <typename T>
unsigned int countOf(const Node<T>* list, const T& value) {
    unsigned result = 0;

    while (list != nullptr) {
        if (list->value == value) {
            ++result;
        }
        list = list->next;
    }
    return result;
}

int main() {
    Node<int> l(1);

    l.add(2);
    l.add(3);
    l.add(1);
    l.add(1);

    std::cout << countOf(&l, 1) << std::endl;

    return 0;
}