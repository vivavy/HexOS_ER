#pragma once

#include "log.h"
#include "string.h"

namespace log {
    class Stream { public:
        Stream();
        ~Stream();
        Stream operator<<(String s);
    };

    extern Stream debug;
    extern Stream info;
    extern Stream warn;
    extern Stream error;
    extern Stream fatal;
}
