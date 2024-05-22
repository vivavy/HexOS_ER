#pragma once

#include <object.hh>
#include <vheap.hh>
#include <utils.hh>

class String : public Object {
private:
    char* data;
    usize length;

    void allocateAndCopy(const char* str, usize len) {
        data = static_cast<char*>(vheap::alloc(len + 1));
        utils::memory::copy(data, str, len);
        data[len] = '\0';
        length = len;
    }
public:
    String(const char* str = "") {
        usize len = 0;
        while (str[len] != '\0') ++len;
        allocateAndCopy(str, len);
    }

    String(const String& other) {
        allocateAndCopy(other.data, other.length);
    }

    ~String() {
        vheap::free((u32)data, length + 1);
    }

    const char* getType() const {
        return "String";
    }

    Object* clone() const {
        return new String(*this);
    }

    String& operator=(const String& other) {
        if (this != &other) {
            vheap::free((u32)data, length + 1);
            allocateAndCopy(other.data, other.length);
        }
        return *this;
    }

    bool operator==(const String& other) const {
        if (length != other.length) return false;
        return utils::memory::compare(data, other.data, length) == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    // Конкатенация строк
    String operator+(const String& other) const {
        usize newLength = length + other.length;
        char* newData = static_cast<char*>(vheap::alloc(newLength + 1));
        utils::memory::copy(newData, data, length);
        utils::memory::copy(newData + length, other.data, other.length);
        newData[newLength] = '\0';

        String newString(newData);
        vheap::free((u32)newData, newLength + 1);
        return newString;
    }

    String& operator+=(const String& other) {
        *this = *this + other;
        return *this;
    }

    const char* c_str() const {
        return data;
    }

    usize size() const {
        return length;
    }
};
