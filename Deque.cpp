#include "Deque.hpp"

template <typename T>
Deque<T>::Deque() : head(nullptr), tail(nullptr) {}

template <typename T>
Deque<T>::~Deque() {
    while (!isEmpty()) pop_front();
}
template <typename T>
void Deque<T>::push_front(const T& value) {
    Node* node = new Node(value);
    if (isEmpty()) {
        head = tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
}

template <typename T>
void Deque<T>::push_back(const T& value) {
    Node* node = new Node(value);
    if (isEmpty()) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

template <typename T>
void Deque<T>::pop_front() {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    Node* temp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    delete temp;
}

template <typename T>
void Deque<T>::pop_back() {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    Node* temp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete temp;
}

template <typename T>
T Deque<T>::front() const {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    return head->data;
}

template <typename T>
T Deque<T>::back() const {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    return tail->data;
}

template <typename T>
bool Deque<T>::isEmpty() const {
    return head == nullptr;
}

//explicit template instantiation
template class Deque<std::string>;
