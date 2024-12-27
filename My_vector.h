#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>

template <typename T>
class My_vector {
private:
    T* data;           
    size_t capacity;   
    size_t size;       

    void resize(size_t newCapacity);  

public:
    My_vector();                       
    ~My_vector();                      
    void push_back(const T& value); 
    void pop_back();                
    T& operator[](size_t index);   
    const T& operator[](size_t index) const; 
    size_t getSize() const;         
    size_t getCapacity() const;     
    bool isEmpty() const;           

    // Iterator support
    T* begin();                    
    T* end();                       
    const T* begin() const;         
    const T* end() const;           
};


template <typename T>
My_vector<T>::My_vector() : data(nullptr), capacity(0), size(0) {}


template <typename T>
My_vector<T>::~My_vector() {
    delete[] data;  
}


template <typename T>
void My_vector<T>::resize(size_t newCapacity) {
    if (newCapacity < size) {
        throw std::invalid_argument("New capacity must be greater than current size.");
    }
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}



template <typename T>
void My_vector<T>::push_back(const T& value) {
    if (size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);  
    }
    data[size++] = value;  
}


template <typename T>
void My_vector<T>::pop_back() {
    if (size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    --size;  
}


template <typename T>
T& My_vector<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];  
}

template <typename T>
const T& My_vector<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}


template <typename T>
size_t My_vector<T>::getSize() const {
    return size;  
}


template <typename T>
size_t My_vector<T>::getCapacity() const {
    return capacity;  
}


template <typename T>
bool My_vector<T>::isEmpty() const {
    return size == 0;  
}


template <typename T>
T* My_vector<T>::begin() {
    return data;  
}

template <typename T>
T* My_vector<T>::end() {
    return data + size;  
}

template <typename T>
const T* My_vector<T>::begin() const {
    return data;  
}

template <typename T>
const T* My_vector<T>::end() const {
    return data + size; 
}

#endif 
