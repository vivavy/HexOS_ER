#pragma once

#include "types.h"

namespace utils {
    namespace memory {
        void copy(const void *, const void *, usize);
        bool compare(const void *, const void *, usize);
        u32 strlen(const void *);
        bool strEqual(const void *, const void *);
    }
    namespace convert {
        const char *itoa(int);
    }
}
