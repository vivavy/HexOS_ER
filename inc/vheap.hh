#pragma once

#include "oop.hh"

namespace vheap {
    char* buffer;
    U32 size;
    char* bitmap;

    void init();
    void* alloc(usize size);
    void free(void *ptr, usize size);
}
