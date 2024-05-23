// Port IO : Port I/O functions : 0.0.5-rev0

#include <portio.h>

u32 port::inl(u32 portnim) {
    u32 data = 0;
    asm volatile("inl %1, %0" : "=a"(data) : "d"(portnim));
    return data;
}

void port::outl(u32 portnim, u32 data) {
    asm volatile("outl %0, %1" : : "a"(data), "d"(portnim));
}

u16 port::inw(u32 portnim) {
    u16 data = 0;
    asm volatile("inw %1, %0" : "=a"(data) : "d"(portnim));
    return data;
}

void port::outw(u32 portnim, u16 data) {
    asm volatile("outw %0, %1" : : "a"(data), "d"(portnim));
}

u8 port::inb(u32 portnim) {
    u8 data = 0;
    asm volatile("inb %1, %0" : "=a"(data) : "d"(portnim));
    return data;
}

void port::outb(u32 portnim, u8 data) {
    asm volatile("outb %0, %1" : : "a"(data), "d"(portnim));
}
