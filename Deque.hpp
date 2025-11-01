#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <stdexcept>
#include <string>

template <typename T>
class Deque {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    Deque();
    ~Deque();
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    T front() const;
    T back() const;
    bool isEmpty() const;
};

#endif
