// Log : Logging implementation : 0.0.1-rev2

#include <log.h>

log::Stream::Stream() {}
log::Stream::~Stream() {}
log::Stream log::Stream::operator<<(String s) {
    return *this;
}

log::Stream log::debug = log::Stream();
log::Stream log::info = log::Stream();
log::Stream log::warn = log::Stream();
log::Stream log::error = log::Stream();
log::Stream log::fatal = log::Stream();
