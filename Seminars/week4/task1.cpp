#include <iostream>
#include <queue>

template <typename T>
void printQueue(std::queue<T> q) {
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

template <typename T>
std::queue<T> dropEverySecond(std::queue<T> inputQ) {
    std::queue<T> result;
    bool keep = true;

    while (!inputQ.empty()) {
        T element = inputQ.front();
        inputQ.pop();

        if (keep) {
            result.push(element);
        }
        keep = !keep;
    }
    return result;
}

int main() {
    std::queue<int> myQueue;
    myQueue.push(1);
    myQueue.push(2);
    myQueue.push(3);
    myQueue.push(4);
    myQueue.push(5);

    printQueue(myQueue);

    std::queue<int> filteredQueue = dropEverySecond(myQueue);

    printQueue(filteredQueue);

    return 0;
}