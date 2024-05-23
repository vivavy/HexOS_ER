// DRY Utils : Shortcut implemetation to follow DRY principle : 0.0.1-rev13

#include <utils.h>

void utils::memory::copy(const void *src, const void *dst, usize size) {
    for (usize i = 0; i < size; i++) {
        u8* dstPtr = (u8*)((u32)dst + i);
        u8* srcPtr = (u8*)((u32)src + i);
        *dstPtr = *srcPtr;
    }
}

bool utils::memory::compare(const void *a, const void *b, usize size) {
    for (usize i = 0; i < size; i++) {
        u8 *aAdr = (u8*)((u32)a + i);
        u8 *bAdr = (u8*)((u32)b + i);
        if (*aAdr != *bAdr) {
            return false;
        }
    }
    return true;
}
