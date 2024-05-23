#include "types.h"

namespace uart {
    void init(void);
    void send(const char *s);
    const char *recv();
}
