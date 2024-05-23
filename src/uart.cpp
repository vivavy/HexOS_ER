// x86-UART : UART implementation based on port I/O : 0.9.3-rev34

#include <uart.h>
#include <portio.h>

/*

section .text
global uart_initialize
global uart_is_recieve_buffer_empty
global uart_getchar
global uart_is_transmit_buffer_empty
global uart_putchar
global uart_puts

UART_PORT_COM1 equ 0x3F8

uart_initialize:
    mov dx, UART_PORT_COM1 + 1
    mov al, 0x00
    out dx, al

    mov dx, UART_PORT_COM1 + 3
    mov al, 0x80
    out dx, al

    mov dx, UART_PORT_COM1
    mov al, 0x03
    out dx, al

    mov dx, UART_PORT_COM1 + 1
    mov al, 0x00
    out dx, al

    mov dx, UART_PORT_COM1 + 3
    mov al, 0x03
    out dx, al

    mov dx, UART_PORT_COM1 + 2
    mov al, 0xC7
    out dx, al

    mov dx, UART_PORT_COM1 + 4
    mov al, 0x0B
    out dx, al

    ret

uart_is_recieve_buffer_empty:
    mov dx, UART_PORT_COM1 + 5
    in al, dx
    test al, 1
    jnz buffer_not_empty
    xor eax, eax
    ret
buffer_not_empty:
    mov eax, 1
    ret

uart_getchar:
read_loop_start:
    call uart_is_recieve_buffer_empty
    test eax, eax
    jnz read_loop_start
    mov dx, UART_PORT_COM1
    in al, dx
    ret

uart_is_transmit_buffer_empty:
    mov dx, UART_PORT_COM1 + 5
    in al, dx
    test al, 0x20
    jz buffer_not_empty
    mov eax, 1
    ret
buffer_not_empty:
    xor eax, eax
    ret

uart_putchar:
write_loop_start:
    call uart_is_transmit_buffer_empty
    test eax, eax
    jz write_loop_start
    mov dx, UART_PORT_COM1
    mov al, [esp+4]
    out dx, al
    ret

uart_puts:
    pusha
    mov esi, edi
    call strlen
    mov ecx, eax
    xor edx, edx

loop_start:
    mov al, [esi + edx]
    call uart_putchar
    inc edx
    cmp edx, ecx
    jl loop_start

    popa
    ret

*/

void uart::init(void) {
    port::outl(0x3F8, 0);
    port::outl(0x3FB, 0x80);
    port::outl(0x3F8, 0x03);
    port::outl(0x3F9, 0x00);
    port::outl(0x3FB, 0x03);
    port::outl(0x3FA, 0xC7);
    port::outl(0x3FC, 0x0B);
}

bool __uart_is_empty(void) {
    return port::inb(0x3FD) & 0x20 == 0;
}

void __putc(char c) {
    while (!__uart_is_empty())
        ;
    port::outb(0x3F8, c);
}

bool __ready_to_receive(void) {
    return port::inb(0x3FD) & 0x01 == 0;
}

char __getc(void) {
    while (!__ready_to_receive())
        ;
    return port::inb(0x3F8);
}

void uart::send(String s) {
    for (int i = 0; i < s.size(); i++)
        __putc(s[i]);
}

String uart::recv() {
    String rv;
    while (__ready_to_receive())
        rv += __getc();
    return rv;
}
