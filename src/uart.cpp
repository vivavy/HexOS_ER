// x86-UART : UART implementation based on port I/O : 0.9.3-rev27

#include <uart.h>
#include <portio.h>

void uart::init(void) {
    port::outl(uart::EIRQ, 0);
    port::outl(uart::CTRL, 0x80);
    port::outl(uart::BAUD_PORT_LO, 0x03);
    port::outl(uart::BAUD_PORT_HI, 0x00);
    port::outl(uart::CTRL, 0x03);
    port::outl(uart::FIFO, 0xC7);
    port::outl(uart::CTRL_MODEM, 0x0B);
    port::outl(uart::CTRL_MODEM, 0x1E);
}

void uart::send(String s) {
    for (int i = 0; i < s.size(); i++)
        while (!(port::inb(uart::STATE_LINE) & 0x20))
            port::outb(uart::TX, s[i]);
}

String uart::recv() {
    String rv;
    while (!(port::inb(uart::STATE_LINE) & 1))
        rv += port::inb(uart::RX);
    return rv;
}
