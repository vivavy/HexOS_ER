#pragma once

#include <oop.hh>

namespace log {
    class Stream : public Object { public:
        Stream();
        ~Stream();
        Stream operator<<(String s);
    };

    Stream debug;
    Stream info;
    Stream warn;
    Stream error;
    Stream fatal;
}
