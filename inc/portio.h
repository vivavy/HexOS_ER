#include "types.h"


namespace port {
    u32 inl(u32 portnim);
    void outl(u32 portnim, u32 data);
    u16 inw(u32 portnim);
    void outw(u32 portnim, u16 data);
    u8 inb(u32 portnim);
    void outb(u32 portnim, u8 data);
}
