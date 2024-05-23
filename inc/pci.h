#pragma once

#include "types.h"
#include "array.h"

namespace pci {
    class Device {
        void __updateInfo();
        bool isMeNull;
    public:
        u16 vendor;
        u16 device;
        u8 classCode;
        u8 subClassCode;
        u8 progIf;
        u8 revId;
        u8 bus;
        u8 slot;

        Device();
        Device(u8 bus, u8 slot);
        ~Device();

        void printInfo();

        bool exists();

        explicit operator bool() const {
            return !isMeNull;
        };
    };

    u32 devRead(u8 bus, u8 slot, u8 func, u8 offset);
    void devWrite(u8 bus, u8 slot, u8 func, u8 offset, u32 data);
    Array<pci::Device> findDeviceByClass(u8 classCode, int maxDevices);
    Array<pci::Device> getDevices(int maxDevices);
    const char *getVendorName(u32 vendorId);
    const char *getClassName(int classCode);

    extern const char *vendorNames[65536];
    extern const int Noclass;
    extern const int MassStorageController;
    extern const int NetworkController;
    extern const int DisplayController;
    extern const int MultimediaController;
    extern const int MemoryController;
    extern const int BridgeDevice;
    extern const int CommunicationController;
    extern const int GenericSystemPeripheral;
    extern const int InputDeviceController;
    extern const int DockingStation;
    extern const int Processor;
    extern const int SerialBusController;
    extern const int WirelessController;
    extern const int IntelligentController;
    extern const int SatelliteCommunicationController;
    extern const int EncryptionController;
    extern const int SignalProcessingController;
    extern const int ProcessingAccelerator;
    extern const int NonEssentialInstrumentation;
    extern const int Coprocessor;
    extern const int Unknown;
}
