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
            std::cout << current->value << "->";
            current = current->next;
        }
        std::cout << current->value << std::endl;
    }
};

template<typename T>
Node<T>* reverse(Node<T>* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Node<T>* rest = reverse(head->next);
    head->next->next = head;
    head->next = nullptr;

    return rest;
}


int main () {
    Node<int>* l  = new Node<int>(1);
    l->add(2);
    l->add(3);
    l->add(4);
    l->add(5);
    l->add(6);
    l->add(7);

    l->print();
    l = reverse(l);
    l->print();

    delete l;
    return 0;
}