#pragma once

#include <object.hh>
#include <types.hh>

template <typename T>
class PrimitiveClass : public Object {
private:
    T value;
public:
    PrimitiveClass(T val);
    
    const char* getType() const;
    
    Object* clone() const;
    
    PrimitiveClass& operator=(const PrimitiveClass& other);
    
    PrimitiveClass operator+(const PrimitiveClass& other) const;
    PrimitiveClass operator-(const PrimitiveClass& other) const;
    PrimitiveClass operator*(const PrimitiveClass& other) const;
    PrimitiveClass operator/(const PrimitiveClass& other) const;
    
    PrimitiveClass& operator+=(const PrimitiveClass& other);
    PrimitiveClass& operator-=(const PrimitiveClass& other);
    PrimitiveClass& operator*=(const PrimitiveClass& other);
    PrimitiveClass& operator/=(const PrimitiveClass& other);
    
    bool operator==(const PrimitiveClass& other) const;
    bool operator!=(const PrimitiveClass& other) const;
    bool operator<(const PrimitiveClass& other) const;
    bool operator<=(const PrimitiveClass& other) const;
    bool operator>(const PrimitiveClass& other) const;
    bool operator>=(const PrimitiveClass& other) const;

    T getValue() const;
    void setValue(T val);
    T raw() const;
};

template <typename T>
class PrimitiveClassModulo : public PrimitiveClass<T> {
public:
    T operator%(const PrimitiveClassModulo& other) const;
    PrimitiveClassModulo operator%=(const PrimitiveClassModulo& other);
};

using Int = PrimitiveClassModulo<int>;
using Float = PrimitiveClass<double>;
using Half = PrimitiveClass<float>;
using Bool = PrimitiveClass<bool>;
using Char = PrimitiveClass<char>;
using U8 = PrimitiveClass<u8>;
using U16 = PrimitiveClass<u16>;
using U32 = PrimitiveClass<u32>;
using U64 = PrimitiveClass<u64>;
using I8 = PrimitiveClass<i8>;
using I16 = PrimitiveClass<i16>;
using I32 = PrimitiveClass<i32>;
using I64 = PrimitiveClass<i64>;
using Usize = PrimitiveClass<usize>;
using Pointer = PrimitiveClass<usize>;

using Size = Usize;