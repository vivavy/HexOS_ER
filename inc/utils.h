#pragma once

#include "types.h"

namespace utils {
    namespace memory {
        void copy(const void *dst, const void *src, usize size);
        bool compare(const void *a, const void *b, usize size);
    }
}
