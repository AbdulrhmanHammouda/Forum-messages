#ifndef MY_STACK_H
#define MY_STACK_H

#include <stdexcept>

template <typename T>
class My_stack {
private:
    class Node {
        T data;
        Node* next;
        Node(const T& value, Node* nextNode = nullptr) : data(value), next(nextNode) {}
    };
    Node* topNode;
    size_t size;

public:
    My_stack() : topNode(nullptr), size(0) {}
    ~My_stack();

    void push(const T& value);
    void pop();
    T& top();
    bool isEmpty() const;
    size_t getSize() const;
};

template <typename T>
My_stack<T>::~My_stack() {
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
void My_stack<T>::push(const T& value) {
    topNode = new Node(value, topNode);
    ++size;
}

template <typename T>
void My_stack<T>::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    Node* temp = topNode;
    topNode = topNode->next;
    delete temp;
    --size;
}

template <typename T>
T& My_stack<T>::top() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return topNode->data;
}

template <typename T>
bool My_stack<T>::isEmpty() const {
    return topNode == nullptr;
}

template <typename T>
size_t My_stack<T>::getSize() const {
    return size;
}

#endif 
