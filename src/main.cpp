#include <calls.hh>
#include <oop.hh>


nomangle naked
void kmain() {
    *((char*)0xb8000) = 'X';
    asm volatile ("hlt");
}
