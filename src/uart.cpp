// x86-UART : UART implementation based on port I/O : 0.10.1-rev5

#include <uart.h>
#include <portio.h>
#include <vheap.h>


void uart::init(void) {
    port::outb(0x3F8, 0);
    port::outb(0x3FB, 0x80);
    port::outb(0x3F8, 0x03);
    port::outb(0x3F9, 0x00);
    port::outb(0x3FB, 0x03);
    port::outb(0x3FA, 0xC7);
    port::outb(0x3FC, 0x0B);
}

void __putc(char c) {
    port::outb(0x3F8, c);
}

char __getc(void) {
    return port::inb(0x3F8);
}

void uart::send(const char *s) {
    for (int i = 0; s[i] != '\0'; i++)
        __putc(s[i]);
}

const char *uart::recv() {
    char *buf;

    buf = static_cast<char*>(vheap::alloc(256));

    int i = 0;
    
    do
        buf[i++] = __getc();
    while (buf[i] != '\0' && i < 256);

    buf[i] = '\0';

    return buf;
}
