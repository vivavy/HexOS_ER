#include <list.hh>
#include <oop.hh>

template <typename T>
void List<T>::resize(usize newCapacity) {
    T* newData = static_cast<T*>(vheap::alloc(newCapacity * sizeof(T)));
    utils::memory::copy(newData, data, size * sizeof(T));
    vheap::free(data, capacity * sizeof(T));
    data = newData;
    capacity = newCapacity;
}

template <typename T>
List<T>::List(usize initialCapacity)
    : capacity(initialCapacity), size(0) {
    data = static_cast<T*>(vheap::alloc(capacity * sizeof(T)));
}

template <typename T>
List<T>::List(const List& other)
    : capacity(other.capacity), size(other.size) {
    data = static_cast<T*>(vheap::alloc(capacity * sizeof(T)));
    utils::memory::copy(data, other.data, size * sizeof(T));
}

template <typename T>
List<T>::~List() {
    vheap::free(data, capacity * sizeof(T));
}

template <typename T>
const char* List<T>::getType() const {
    return "List";
}

template <typename T>
Object* List<T>::clone() const {
    return new List(*this);
}

template <typename T>
void List<T>::add(const T& item) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = item;
}

template <typename T>
void List<T>::removeAt(usize index) {
    if (index < size) {
        for (usize i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }
}

template <typename T>
T& List<T>::operator[](usize index) {
    return data[index];
}

template <typename T>
const T& List<T>::operator[](usize index) const {
    return data[index];
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        vheap::free(data, capacity * sizeof(T));
        capacity = other.capacity;
        size = other.size;
        data = static_cast<T*>(vheap::alloc(capacity * sizeof(T)));
        utils::memory::copy(data, other.data, size * sizeof(T));
    }
    return *this;
}

template <typename T>
Usize List<T>::getSize() const {
    return size;
}

template <typename T>
Usize List<T>::getCapacity() const {
    return capacity;
}
