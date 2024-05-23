#pragma once

#include "types.h"
#include "list.h"

namespace pci {
    class Device { public:
        u16 vendorId;
        u16 deviceId;
        u8 classCode;
        u8 subClassCode;
        u8 progIf;
        u8 revId;

        Device(u16 vendorId, u16 deviceId, u8 classCode, u8 subClassCode, u8 progIf, u8 revId);
        ~Device();

        bool exists();
    };

    static void confWrite();
    static void confRead();
    static u32 read(u8 bus, u8 slot, u8 func, u8 offset);
    static bool checkDevice(u8 bus, u8 slot, pci::Device& device);
    static List<pci::Device> findDeviceByClass(u8 classCode, int maxDevices, int& count);
    static List<pci::Device> getDevices(int maxDevices);
}
