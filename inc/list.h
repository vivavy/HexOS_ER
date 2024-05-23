#pragma once

#include "types.h"

template <typename T>

class List { private:
    T* data;
    usize capacity;
    usize size;

    void resize(usize newCapacity);
public:
    List(usize initialCapacity);

    List(const List& other);

    ~List();

    const char* getType() const;

    List<T>* clone() const;

    void add(const T& item);

    void removeAt(usize index);

    T& operator[](usize index);

    const T& operator[](usize index) const;

    List& operator=(const List& other);

    usize getSize() const;

    usize getCapacity() const;
};
