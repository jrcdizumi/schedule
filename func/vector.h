#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
class Vector {
private:
    T* data;
    int size;
    int capacity;

public:
    Vector();
    Vector(int capacity);
    Vector(const Vector<T>& other);
    Vector(int capacity, const T& initial);
    ~Vector();

    void push_back(const T& element);
    void pop_back();
    void clear();
    void resize(int newSize);

    T front();
    T back();
    T& operator[](int index);
    const T& operator[](int index) const;

    int getSize() const;
    int getCapacity() const;

    Vector<T>& operator=(const Vector<T>& other);
};

template <typename T>
T Vector<T>::front(){
    return data[0];
}
template <typename T>
T Vector<T>::back(){
    return data[size-1];
}
template <typename T>
Vector<T>::Vector() {
    data = nullptr;
    size = 0;
    capacity = 0;
}

template <typename T>
Vector<T>::Vector(int capacity) {
    data = new T[capacity];
    size = 0;
    this->capacity = capacity;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) {
    data = new T[other.capacity];
    size = other.size;
    capacity = other.capacity;
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template <typename T>
Vector<T>::Vector(int capacity, const T& initial) {
    data = new T[capacity];
    size = capacity;
    this->capacity = capacity;
    for (int i = 0; i < size; i++) {
        data[i] = initial;
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template <typename T>
void Vector<T>::push_back(const T& element) {
    if (size == capacity) {
        capacity = capacity == 0 ? 1 : capacity * 2;
        T* newData = new T[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    data[size++] = element;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size > 0) {
        size--;
    }
}

template <typename T>
void Vector<T>::clear() {
    size = 0;
}
template <typename T>
void Vector<T>::resize(int newSize) {
    if (newSize > capacity) {
        capacity = newSize;
        T* newData = new T[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    size = newSize;
    return;
}

template <typename T>
T& Vector<T>::operator[](int index) {
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const {
    return data[index];
}

template <typename T>
int Vector<T>::getSize() const {
    return size;
}

template <typename T>
int Vector<T>::getCapacity() const {
    return capacity;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        delete[] data;
        data = new T[other.capacity];
        size = other.size;
        capacity = other.capacity;
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}
#endif // VECTOR_H
