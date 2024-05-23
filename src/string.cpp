// String : String class : 0.1.9-rev21

#include <string.h>
#include <utils.h>
#include <vheap.h>

void String::allocateAndCopy(const char* str, usize len) {
    data = static_cast<char*>(vheap::alloc(len + 1));
    utils::memory::copy(data, str, len);
    data[len] = '\0';
    length = len;
}

String::String() {
    data = static_cast<char*>(vheap::alloc(1));
    data[0] = '\0';
    length = 0;
}

String::String(char c) {
    data = static_cast<char*>(vheap::alloc(2));
    data[0] = c;
    data[1] = '\0';
    length = 1;
}

String::String(const char* str = "") {
    usize len = 0;
    while (str[len] != '\0') ++len;
    allocateAndCopy(str, len);
}

String::String(const String& other) {
    allocateAndCopy(other.data, other.length);
}

String::~String() {
    vheap::free(data, length + 1);
}

bool String::operator==(const String& other) const {
    if (length != other.length) return false;
    return utils::memory::compare(data, other.data, length) == 0;
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}

String String::operator+(const String& other) const {
    usize newLength = length + other.length;
    char* newData = static_cast<char*>(vheap::alloc(newLength + 1));
    utils::memory::copy(newData, data, length);
    utils::memory::copy(newData + length, other.data, other.length);
    newData[newLength] = '\0';

    String newString(newData);
    vheap::free(newData, newLength + 1);
    return newString;
}

String& String::operator+=(const String& other) {
    usize newLength = length + other.length;
    char* newData = static_cast<char*>(vheap::alloc(newLength + 1));
    utils::memory::copy(newData, data, length);
    utils::memory::copy(newData + length, other.data, other.length);
    newData[newLength] = '\0';

    vheap::free(data, length + 1);
    data = newData;
    length = newLength;
    return *this;
}

char String::operator[](usize index) const {
    return data[index];
}

const char* String::c_str() const {
    return data;
}

usize String::size() const {
    return length;
}
