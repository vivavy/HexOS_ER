// DRY Utils : Shortcut implemetation to follow DRY principle : 0.0.2-rev0

#include <utils.h>
#include <vheap.h>

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

u32 utils::memory::strlen(const void *ptr) {
    u32 len = 0;
    while (*((u8*)((u32)ptr + len)) != '\0') {
        len++;
    }
    return len;
}

bool utils::memory::strEqual(const void *a, const void *b) {
    u32 lenA = utils::memory::strlen(a);
    u32 lenB = utils::memory::strlen(b);
    if (lenA != lenB) {
        return false;
    }
    return utils::memory::compare(a, b, lenA);
}

const char *utils::convert::itoa(int i) {
    char *str = (char *)vheap::alloc(32);
    int len = 0;
    if (i < 0) {
        str[len++] = '-';
    }
    while (i != 0) {
        str[len++] = '0' + (i % 10);
        i /= 10;
    }
    for (int i = 0; i < len; i++) {
        str[len - i - 1] = str[i];
    }
    str[len] = '\0';
    return str;
}
