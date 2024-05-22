#include <log.hh>
#include <oop.hh>

log::Stream::Stream() {}
log::Stream::~Stream() {}
log::Stream log::Stream::operator<<(String s) {
    return *this;
}
