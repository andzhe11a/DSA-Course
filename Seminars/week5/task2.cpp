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

    void print() const {
        const Node* current = this;
        while (current->next != nullptr) {
            std::cout << current->value << " -> ";
            current = current->next;
        }
        std::cout << current->value << std::endl;
    }
};

template <typename T>
Node<T>* removeAll(Node<T>* list, const T& value) {
    if (list == nullptr) {
        return nullptr;
    }

    Node<T>* next = removeAll(list->next, value);

    if (list->value == value) {
        list->next = nullptr;
        delete list;
        return next;
    }

    list->next = next;
    return list;
}

int main() {
    Node<int>* l  = new Node<int>(1);
    l->add(2);
    l->add(3);
    l->add(1);
    l->add(1);

    l->print();
    l = removeAll(l, 1);
    l->print();

    delete l;

    return 0;
}