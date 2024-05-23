// PCI : PCI interface implementation : 0.4.2-rev3
#include <pci.h>
#include <portio.h>
#include <log.h>
#include <list.h>
#include <vheap.h>
#include <array.h>

constexpr u32 CONFIG_ADDRESS = 0xCF8;
constexpr u32 CONFIG_DATA = 0xCFC;

bool __PCI_check(u8 bus, u8 slot);

u32 __PCI_read(u32 address) {
    port::outl(CONFIG_DATA, address);
    return port::inl(CONFIG_DATA);
}

void __PCI_write(u32 address, u32 data) {
    port::outl(CONFIG_ADDRESS, address);
    port::outl(CONFIG_DATA, data);
}

u32 pci::devRead(u8 bus, u8 slot, u8 func, u8 offset) {
    u32 address;
    address = (u32)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xfc) | ((u32)0x80000000));
    return __PCI_read(address);
}

void pci::devWrite(u8 bus, u8 slot, u8 func, u8 offset, u32 data) {
    u32 address;
    address = (u32)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xfc) | ((u32)0x80000000));
    __PCI_write(address, data);
}

Array<pci::Device> pci::getDevices(int maxDevices) {
    Array<pci::Device> devices(maxDevices);
    u32 arrayIndex = 0;
    bool overflow = false;
    for (u8 bus = 0; bus < 256; ++bus)
        for (u8 slot = 0; slot < 32; ++slot)
            if (__PCI_check(bus, slot)) {
                devices[arrayIndex++] = pci::Device(bus, slot);
                if (arrayIndex == maxDevices) {
                    overflow = true;
                    break;
                }
            }
    if (overflow)
        log::warn << "Maximum number of devices reached (" << maxDevices << ")\n";
    devices[arrayIndex] = pci::Device();
    return devices;
}

Array<pci::Device> pci::findDeviceByClass(u8 classCode, int maxDevices) {
    Array<pci::Device> filteredDevices(maxDevices);
    Array<pci::Device> allDevices = getDevices(maxDevices);
    u32 arrayIndex = 0;
    bool overflow = false;
    for (u32 i = 0; i < maxDevices; ++i) {
        if (allDevices[i].classCode == classCode) {
            filteredDevices[arrayIndex++] = allDevices[i];
            if (arrayIndex == maxDevices) {
                overflow = true;
                break;
            }
        }
    }
    if (overflow)
        log::warn << "Maximum number of devices reached (" << maxDevices << ")\n";
    filteredDevices[arrayIndex] = pci::Device();
    return filteredDevices;
}

bool __PCI_check(u8 bus, u8 slot) {
    u32 data = pci::devRead(bus, slot, 0, 0);
    if ((data & 0xFFFF) == 0xFFFF) return false;
    return true;
}

pci::Device::Device() {
    bus = 0;
    slot = 0;
    vendor = 0;
    device = 0;
    classCode = 0;
    subClassCode = 0;
    progIf = 0;
    revId = 0;
    isMeNull = true;
}

pci::Device::Device(u8 bus, u8 slot) {
    this->bus = bus;
    this->slot = slot;
    this->__updateInfo();
}

pci::Device::~Device() {
    
}

const int pci::Noclass = 0;
const int pci::MassStorageController = 1;
const int pci::NetworkController = 2;
const int pci::DisplayController = 3;
const int pci::MultimediaController = 4;
const int pci::MemoryController = 5;
const int pci::BridgeDevice = 6;
const int pci::CommunicationController = 7;
const int pci::GenericSystemPeripheral = 8;
const int pci::InputDeviceController = 9;
const int pci::DockingStation = 10;
const int pci::Processor = 11;
const int pci::SerialBusController = 12;
const int pci::WirelessController = 13;
const int pci::IntelligentController = 14;
const int pci::SatelliteCommunicationController = 15;
const int pci::EncryptionController = 16;
const int pci::SignalProcessingController = 17;
const int pci::ProcessingAccelerator = 18;
const int pci::NonEssentialInstrumentation = 19;
const int pci::Coprocessor = 0x40;
const int pci::Unknown = 0xFF;

const char *__clsno  = "Noclass";
const char *__mass   = "Mass Storage Controller";
const char *__net    = "Network Controller";
const char *__disp   = "Display Controller";
const char *__multi  = "Multimedia Controller";
const char *__mem    = "Memory Controller";
const char *__bridge = "Bridge Device";
const char *__comm   = "Communication Controller";
const char *__gen    = "Generic System Peripheral";
const char *__input  = "Input Device Controller";
const char *__dock   = "Docking Station";
const char *__proc   = "Processor";
const char *__ser    = "Serial Bus Controller";
const char *__wifi   = "Wireless Controller";
const char *__intel  = "Intelligent Controller";
const char *__sat    = "Satellite Communication Controller";
const char *__enc    = "Encryption Controller";
const char *__sig    = "Signal Processing Controller";
const char *__proca  = "Processing Accelerator";
const char *__non    = "Non-Essential Instrumentation";
const char *__coproc = "Coprocessor";
const char *__unknown= "Unknown";

const char *pci::getClassName(int classCode) {
    switch (classCode) {
        case 0x00: return __clsno;
        case 0x01: return __mass;
        case 0x02: return __net;
        case 0x03: return __disp;
        case 0x04: return __multi;
        case 0x05: return __mem;
        case 0x06: return __bridge;
        case 0x07: return __comm;
        case 0x08: return __gen;
        case 0x09: return __input;
        case 0x0A: return __dock;
        case 0x0B: return __proc;
        case 0x0C: return __ser;
        case 0x0D: return __wifi;
        case 0x0E: return __intel;
        case 0x0F: return __sat;
        case 0x10: return __enc;
        case 0x11: return __sig;
        case 0x12: return __proca;
        case 0x13: return __non;
        case 0x14: return __coproc;
        default: return __unknown;
    }
}

const char *__unkven  = "Unknown";
const char *__safenet = "SafeNet";
const char *__allied  = "Allied Telesis, Inc";
const char *__loongson = "Loongson Technology LLC";
const char *__fnlink  = "Fn-Link Technology Limited";
const char *__peak    = "PEAK-System Technik GmbH";
const char *__lockheed = "Lockheed Martin-Marietta Corp";
const char *__tiger   = "Tiger Jet Network, Inc";
const char *__hauppa  = "Hauppauge computer works Inc";
const char *__nebula  = "Nebula Electronics Ltd";
const char *__silicon = "Silicon Image, Inc. (Wrong ID)";
const char *__tele    = "Teles AG";
const char *__ncipher = "nCipher Security";
const char *__general = "General Dynamics";
const char *__dellinc = "Dell Inc";
const char *__level1  = "LevelOne";
const char *__oxide   = "Oxide Computer Company";
const char *__dell    = "Dell";
const char *__compaq  = "Compaq Computer Corporation";
const char *__solidig = "Solidigm";
const char *__hauppai = "Hauppauge computer works Inc";
const char *__davicom = "Davicom Semiconductor, Inc";
const char *__speedtr = "SpeedStream";
const char *__xfxpine = "XFX Pine Group Inc";
const char *__hewlett = "Hewlett-Packard Company";
const char *__zyxelco = "ZyXEL Communications Corporation";
const char *__skelect = "SK-Electronics Co., Ltd";
const char *__ttechco = "TTTech Computertechnik AG";
const char *__scmmicro = "SCM Microsystems, Inc";
const char *__dellin  = "Dell Inc";
const char *__lighti  = "Lightelligence";
const char *__dynalin = "Dynalink";
const char *__sapphir = "Sapphire, Inc";
const char *__jingjia = "Jingjia Microelectronics Co Ltd";    
const char *__ubiqui  = "Ubiquiti Networks, Inc";
const char *__wired   = "Wired Inc";
const char *__dlink   = "D-Link System Inc";
const char *__t1042   = "T1042";
const char *__via     = "VIA Technologies, Inc";
const char *__brea    = "BREA Technologies Inc";
const char *__rhino   = "Rhino Equipment Corp";
const char *__bachman = "Bachmann electronic GmbH";
const char *__pref    = "Preferred Networks, Inc";
const char *__compaq2 = "Compaq Computer Corporation";
const char *__haSoTec = "HaSoTec GmbH";
const char *__shf     = "SHF Communication Technologies AG";
const char *__acrox   = "Acrox Technologies Co., Ltd";

const char *pci::getVendorName(u32 vendorId) {
    switch (vendorId) {
        case 0x0000: return __unkven;
        case 0x0001: return __safenet;
        case 0x0010: return __allied;
        case 0x0014: return __loongson;
        case 0x0018: return __fnlink;
        case 0x001C: return __peak;
        case 0x003D: return __lockheed;
        case 0x0059: return __tiger;
        case 0x0070: return __hauppa;
        case 0x0071: return __nebula;
        case 0x0095: return __silicon;
        case 0x00A7: return __tele;
        case 0x0100: return __ncipher;
        case 0x0123: return __general;
        case 0x0128: return __dell;
        case 0x018A: return __level1;
        case 0x01DE: return __oxide;
        case 0x0200: return __dell;
        case 0x021B: return __compaq;
        case 0x025E: return __solidig;
        case 0x0270: return __hauppai;
        case 0x0291: return __davicom;
        case 0x02AC: return __speedtr;
        case 0x02E0: return __xfxpine;
        case 0x0303: return __hewlett;
        case 0x0308: return __zyxelco;
        case 0x0315: return __skelect;
        case 0x0432: return __scmmicro;
        case 0x0497: return __dellin;
        case 0x060E: return __lighti;
        case 0x0675: return __dynalin;
        case 0x0721: return __sapphir;
        case 0x0731: return __jingjia;
        case 0x0777: return __ubiqui;
        case 0x0795: return __wired;
        case 0x07D1: return __dlink;
        case 0x0824: return __t1042;
        case 0x0925: return __via;
        case 0x0A89: return __brea;
        case 0x0B0B: return __rhino;
        case 0x0BAE: return __bachman;
        case 0x0CCD: return __pref;
        case 0x0E11: return __compaq2;
        case 0x0E55: return __haSoTec;
        case 0x0EAC: return __shf;
        case 0x0F62: return __acrox;
        default: return __unkven;
    }
}

void pci::Device::__updateInfo() {
    u32 data = pci::devRead(bus, slot, 0, 0);
    vendor = (data & 0xFFFF0000) >> 16;
    device = data & 0x0000FFFF;
    data = pci::devRead(bus, slot, 0, 8);
    classCode = (data >> 24) & 0xFF;
    subClassCode = (data >> 16) & 0xFF;
    progIf = (data >> 8) & 0xFF;
    revId = data & 0xFF;
}

void pci::Device::printInfo() {
    log::log << "Bus: " << bus << "\n";
    log::log << "Slot: " << slot << "\n";
    log::log << "Vendor: " << pci::getVendorName(vendor) << "\n";
    log::log << "Device: " << device << "\n";
    log::log << "Class Code: " << pci::getClassName(classCode) << "\n";
    log::log << "Subclass Code: " << subClassCode << "\n";
    log::log << "Programming Interface: " << progIf << "\n";
    log::log << "Revision ID: " << revId << "\n";
}

