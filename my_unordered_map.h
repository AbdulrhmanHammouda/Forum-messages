#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <functional>
#include <stdexcept>
#include <iostream>
#include "My_vector.h"
using namespace std;

template <typename KeyType, typename ValueType>
class my_unordered_map {
private:
    class Node {
    public:
        KeyType key;
        ValueType value;
        Node* next;

        Node(const KeyType& k, const ValueType& v) : key(k), value(v), next(nullptr) {}
        ~Node() = default;
    };

    static const int TABLE_SIZE = 100;
    Node* table[TABLE_SIZE];

    int hash(const KeyType& key) const {
        return std::hash<KeyType>()(key) % TABLE_SIZE;
    }

public:
    my_unordered_map() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    ~my_unordered_map() {
        clear();
    }

    void insert(const KeyType& key, const ValueType& value) {
        int index = hash(key);
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    bool find(const KeyType& key, ValueType*& value) const {
        int index = hash(key);
        Node* current = table[index];
        while (current) {
            if (current->key == key) {
                value = &current->value;
                return true;
            }
            current = current->next;
        }
        value = nullptr;
        return false;
    }

    bool erase(const KeyType& key) {
        int index = hash(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    table[index] = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    void clear() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
            table[i] = nullptr;
        }
    }

    bool isEmpty() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i] != nullptr) {
                return false;
            }
        }
        return true;
    }

    My_vector<KeyType> getKeys() const {
        My_vector<KeyType> keys;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current) {
                keys.push_back(current->key);
                current = current->next;
            }
        }
        return keys;
    }
};

#endif
