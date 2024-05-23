#pragma once

#include "types.h"

template <typename T>
class Array {
    T *data;
    usize mySize;

public:
    Array(usize mySize);
    ~Array();

    T &operator[](usize index);
    const T &operator[](usize index) const;

    explicit operator bool() const;

    usize size() const;
};
