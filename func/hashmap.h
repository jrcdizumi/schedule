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
    typedef unsigned int uint;
private:
    HashNode<T>** table;
    uint capacity;
    uint p = 31;
public:
    //初始化哈希表
    HashMap(uint capacity = 200,uint prime=31);
    //析构函数
    ~HashMap();
    //返回key的hash值
    uint hash(std::string key);
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

    bool inhash(std::string key);
};

template <typename T>
bool HashMap<T>::inhash(std::string key){
    uint index = hash(key);
    HashNode<T>* node = table[index];
    while (node != nullptr) {
        if (node->key == key) {
            return true;
        }
        node = node->next;
    }
    return false;
}
// Constructor
template <typename T>
HashMap<T>::HashMap(uint capacity,uint prime): capacity(capacity),p(prime) {
    // this->capacity = capacity;
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
unsigned int HashMap<T>::hash(std::string key) {
    uint hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash = ((hash * p + key[i] ) % capacity +capacity)%capacity;
    }
    return hash;
}

// Insert key-value pair
template <typename T>
void HashMap<T>::insert(std::string key, T value) {
    if(key=="")
        return;
    uint index = hash(key);
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
    uint index = hash(key);
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
    uint index = hash(key);
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
    uint index = hash(key);
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
