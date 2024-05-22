#pragma once

#include <oop.hh>
#include <vheap.hh>
#include <utils.hh>
#include <types.hh>

template <typename T>
class List : public Object {
private:
    T* data;
    usize capacity;
    usize size;

    void resize(usize newCapacity);
public:
    List(usize initialCapacity);

    List(const List& other);

    ~List();

    const char* getType() const;

    Object* clone() const;

    void add(const T& item);

    void removeAt(usize index);

    T& operator[](usize index);

    const T& operator[](usize index) const;

    List& operator=(const List& other);

    Usize getSize() const;

    Usize getCapacity() const;
};
