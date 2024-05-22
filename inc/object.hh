#pragma once

#include <types.hh>
#include <oop.hh>
#include <vheap.hh>

class Object {
public:
    ~Object() {}
    const char* getType() const;
    Object* clone() const;

    void* operator new(usize size);

    void operator delete(void* ptr);
};
