// Virtual Heap : Virtual private kernel heap implementation : 0.3.1-rev7

#include <vheap.h>

char* vheap::buffer;
u32 vheap::size;
char* vheap::bitmap;

void vheap::init() {
    vheap::buffer = (char*)(1024*1024);
    vheap::size = 1024*1024;
    vheap::bitmap = (char*)(1024*1024*2);

    for (u32 i = 0; i < size / 8; i++) {
        bitmap[i] = 0;
    }
}

void* vheap::alloc(usize size) {
    u32 start = 0;
    u8 bits = 0;
    u8 block;
    u32 got;
    bool lookup = true;
    for (u32 i = 0; i < vheap::size / 8; i+=1) {
        if (lookup) {
            start = i * 8;
            lookup = false;
        }
        block = vheap::bitmap[i];
        for (u32 bitnum = 0; bitnum < 8; bitnum++) {
            if (block & (1 << bitnum)) {
                i++; lookup = true; break;
            }
            got++;
            if (size == got) {
                return (void*)(vheap::buffer + start);
            }
        }
    }
    return nullptr;
}

void vheap::free(void *ptr, usize size) {
    u32 start_bytes = (u32)ptr / 8;
    u32 start_bit = (u32)ptr % 8;
    while (size) {
        for (u32 bitnum = 0; bitnum < 8; bitnum++) {
            vheap::bitmap[start_bytes] &= ~(1 << bitnum);
        }
        size -= 8;
        start_bytes++;
    }

    return;
}
