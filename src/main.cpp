// Main : Main kernel file for the project. : 0.0.3-rev21

#include <calls.h>
#include <uart.h>
#include <pci.h>
#include <list.h>
#include <utils.h>
#include <array.h>

nomangle
void kmain() {
    uart::init();
    uart::send("Found some devices for you!\n");

    Array<pci::Device> devices = pci::getDevices(256);

    for (usize i = 0; i < devices.size(); i++) {
        devices[i].printInfo();
        uart::send("\n\n");
    }
}
