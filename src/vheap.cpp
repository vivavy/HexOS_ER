#include <vheap.hh>
#include <oop.hh>

void vheap::init() {
    vheap::buffer = (char*)(1024*1024);
    vheap::size = 1024*1024;
    vheap::bitmap = (char*)(1024*1024*2);

    for (U32 i = 0; i < size / 8; i+=1) {
        bitmap[i.raw()] = 0;
    }
}

void* vheap::alloc(usize size) {
    // find free area of size
    U32 start = 0;
    u8 bits = 0;
    u8 block;
    u32 got;
    bool lookup = true;
    for (U32 i = 0; i < vheap::size / 8; i+=1) {
        if (lookup) {
            start = i * 8;
            lookup = false;
        }
        block = vheap::bitmap[i.raw()];
        for (u32 bitnum = 0; bitnum < 8; bitnum++) {
            if (block & (1 << bitnum)) {
                i+=1; lookup = true; break;
            }
            got++;
            if (size == got) {
                return (void*)(vheap::buffer + start.raw());
            }
        }
    }
    return nullptr;
}

void vheap::free(Size ptr, Size size) {
    // calculate position in buffer
    U32 start_bytes = (u32)ptr.raw() / 8;
    U32 start_bit = (u32)ptr.raw() % 8;

    // set bits in bitmap to 0
    while (size.raw()) {
        for (u32 bitnum = 0; bitnum < 8; bitnum++) {
            vheap::bitmap[start_bytes.raw()] &= ~(1 << bitnum);
        }
        size -= 8;
        start_bytes+=1;
    }

    return;
}
