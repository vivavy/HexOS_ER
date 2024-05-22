#pragma once

#include <oop.hh>

namespace vheap {
    char* buffer;
    U32 size;
    char* bitmap;

    void init();
    void* alloc(Size size);
    void free(Pointer ptr, Size size);
}
