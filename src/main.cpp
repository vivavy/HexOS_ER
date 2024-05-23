// Main : Main kernel file for the project. : 0.0.3-rev19

#include <calls.h>
#include <uart.h>


nomangle
void kmain() {
    uart::init();
    uart::send("Hello World!\n");
    *((char*)0xb8000) = 'X';
    asm volatile ("hlt");
}
