#pragma once

#include "types.h"

namespace vheap {
    extern char* buffer;
    extern u32 size;
    extern char* bitmap;

    void init();
    void* alloc(usize size);
    void free(void *ptr, usize size);
}
