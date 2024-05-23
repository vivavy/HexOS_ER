#include "types.h"
#include "string.h"

namespace uart {
    void init(void);
    void send(String s);
    String recv();
}
