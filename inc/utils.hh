#pragma once

#include <oop.hh>


namespace utils {
    namespace memory {
        void copy(void* dst, const void* src, Size size) {
            for (usize i = 0; i < size.raw(); ++i) {
                ((u8*)dst)[i] = ((u8*)src)[i];
            }
        }
        int compare(const void* a, const void* b, Size size) {
            for (usize i = 0; i < size.raw(); ++i) {
                if (((u8*)a)[i] < ((u8*)b)[i]) return -1;
                if (((u8*)a)[i] > ((u8*)b)[i]) return 1;
            }
            return 0;
        }
    }
}
