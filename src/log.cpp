// Log : Logging implementation : 0.0.1-rev2

#include <log.h>
#include <uart.h>
#include <utils.h>

log::Stream::Stream(const char *name) {
    this->name = name;
}
log::Stream::~Stream() {}
log::Stream log::Stream::operator<<(const char *s) {
    uart::send(this->name);
    uart::send(s);
    return *this;
}
log::Stream log::Stream::operator<<(const int i) {
    uart::send(this->name);
    uart::send(utils::convert::itoa(i));
    return *this;
}

log::Stream log::debug = log::Stream("[ \033[1;34mDEBUG\033[0m ] ");
log::Stream log::info =  log::Stream("[ \033[1;32mINFO\033[0m  ] ");
log::Stream log::warn =  log::Stream("[ \033[1;33mWARN\033[0m  ] ");
log::Stream log::error = log::Stream("[ \033[1;31mERROR\033[0m ] ");
log::Stream log::fatal = log::Stream("[ \033[1;41mFATAL\033[0m ] ");
log::Stream log::log =  log::Stream("[  \033[1;37mLOG\033[0m  ] ");
