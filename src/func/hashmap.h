#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <iostream>

using namespace std;
template <typename T>
class HashNode {
public:
    std::string key;
    T value;
    HashNode* next;

    HashNode(std::string key, T value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};

template <typename T>
class HashMap {
private:
    HashNode<T>** table;
    int capacity;

public:
    //初始化哈希表
    HashMap(int capacity);
    //析构函数
    ~HashMap();
    //返回key的hash值
    int hash(std::string key);
    //插入key-value
    void insert(std::string key, T value);
    //返回key对应的value
    T get(std::string key);
    //删除key
    void remove(std::string key);
    //更新key对应的value（如果没有该key则新增）
    void update(std::string key, T value);
    //打印哈希表
    void print();
};

// Constructor
template <typename T>
HashMap<T>::HashMap(int capacity) {
    this->capacity = capacity;
    table = new HashNode<T>*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

// Destructor
template <typename T>
HashMap<T>::~HashMap() {
    for (int i = 0; i < capacity; i++) {
        HashNode<T>* node = table[i];
        while (node != nullptr) {
            HashNode<T>* prev = node;
            node = node->next;
            delete prev;
        }
    }
    delete[] table;
}

// Hash function
template <typename T>
int HashMap<T>::hash(std::string key) {
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash = (hash * 31 + key[i] + 128) % capacity;
    }
    return hash;
}

// Insert key-value pair
template <typename T>
void HashMap<T>::insert(std::string key, T value) {
    int index = hash(key);
    HashNode<T>* node = table[index];
    while (node != nullptr) {
        if (node->key == key) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    HashNode<T>* newNode = new HashNode<T>(key, value);
    newNode->next = table[index];
    table[index] = newNode;
}

// Get value by key
template <typename T>
T HashMap<T>::get(std::string key) {
    int index = hash(key);
    HashNode<T>* node = table[index];
    while (node != nullptr) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return T();
}

// Remove key-value pair
template <typename T>
void HashMap<T>::remove(std::string key) {
    int index = hash(key);
    HashNode<T>* node = table[index];
    HashNode<T>* prev = nullptr;
    while (node != nullptr) {
        if (node->key == key) {
            if (prev == nullptr) {
                table[index] = node->next;
            } else {
                prev->next = node->next;
            }
            delete node;
            return;
        }
        prev = node;
        node = node->next;
    }
}
// Update value by key
template <typename T>
void HashMap<T>::update(std::string key, T value) {
    int index = hash(key);
    HashNode<T>* node = table[index];
    while (node != nullptr) {
        if (node->key == key) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    // If key not found, insert new key-value pair
    insert(key, value);
}
// Print all key-value pairs
template <typename T>
void HashMap<T>::print() {
    for (int i = 0; i < capacity; i++) {
        HashNode<T>* node = table[i];
        while (node != nullptr) {
            cout << node->key << ": " << node->value << endl;
            node = node->next;
        }
    }
}

#endif // HASHMAP_H
