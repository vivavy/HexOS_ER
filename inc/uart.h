#include "types.h"
#include "string.h"

namespace uart {
    inline const u32 BASE_PORT = 0x3F8;
    inline const u32 RX = BASE_PORT;
    inline const u32 TX = BASE_PORT;
    inline const u32 EIRQ = BASE_PORT + 1;
    inline const u32 BAUD_PORT_LO = BASE_PORT;
    inline const u32 BAUD_PORT_HI = BASE_PORT + 1;
    inline const u32 FIFO = BASE_PORT + 2;
    inline const u32 CTRL = BASE_PORT + 3;
    inline const u32 CTRL_MODEM = BASE_PORT + 4;
    inline const u32 STATE_LINE = BASE_PORT + 5;
    inline const u32 STATE_MODEM = BASE_PORT + 6;
    inline const u32 SCRETCH = BASE_PORT + 7;


    void init(void);
    void send(String s);
    String recv();
}
