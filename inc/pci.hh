#pragma once

#include <oop.hh>
#include <dev.hh>

namespace pci {
    class Device : public BaseDevice { public:
        U16 vendorId;
        U16 deviceId;
        U8 classCode;
        U8 subClassCode;
        U8 progIf;
        U8 revId;

        Device(U16 vendorId, U16 deviceId, U8 classCode, U8 subClassCode, U8 progIf, U8 revId);
        ~Device();

        bool exists();
    };

    static void confWrite();
    static void confRead();
    static U32 read(U8 bus, U8 slot, U8 func, U8 offset);
    static Bool checkDevice(U8 bus, U8 slot, pci::Device& device);
    static List<pci::Device> findDeviceByClass(U8 classCode, int maxDevices, int& count);
    static List<pci::Device> getDevices(int maxDevices);
}
