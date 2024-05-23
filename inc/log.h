#pragma once

#include "log.h"

namespace log {
    class Stream {
        const char *name;
        
    public:
        Stream(const char *name);
        ~Stream();
        Stream operator<<(const char *s);
        Stream operator<<(const int i);
    };

    extern Stream debug;
    extern Stream info;
    extern Stream warn;
    extern Stream error;
    extern Stream fatal;
    extern Stream log;
}
