// DRY Array : Shortcut implemetation of Array class to follow DRY principle : 0.0.2-rev0

#include <array.h>
#include <vheap.h>

template <typename T>
Array<T>::Array(usize mySize) {
    this->mySize = mySize;
    this->data = (T *)vheap::alloc(mySize * sizeof(T));
}

template <typename T>
Array<T>::~Array() {
    vheap::free(this->data);
}

template <typename T>
T &Array<T>::operator[](usize index) {
    return this->data[index];
}

template <typename T>
const T &Array<T>::operator[](usize index) const {
    return this->data[index];
}

template <typename T>
Array<T>::operator bool() const {
    return this->mySize;
}

template <typename T>
usize Array<T>::size() const {
    return this->mySize;
}