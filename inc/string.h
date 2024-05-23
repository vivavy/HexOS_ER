#pragma once

#include "types.h"

class String {
private:
    char* data;
    usize length;

    void allocateAndCopy(const char* str, usize len);
public:
    String();

    String(char c);

    String(const char* str);

    String(const String& other);

    ~String();

    const char* getType() const;

    String* clone() const;

    String& operator=(const String& other);

    bool operator==(const String& other) const;

    bool operator!=(const String& other) const;

    String operator+(const String& other) const;

    String& operator+=(const String& other);

    char operator[](usize index) const;

    const char* c_str() const;

    usize size() const;
};
