CLEAR := ${CLEAR}
CXXFLAGS := ${CXXFLAGS}
CXXFLAGS += -m32 -nostdlib -fno-builtin -fno-stack-protector -fno-exceptions -fno-rtti -g -O0 -std=c++20 -Iinc
LDFLAGS := ${LDFLAGS}
LDFLAGS += -m elf_i386 -Tlinker.ld -nostdlib


all: clear clean run

clear:
	if [ ${CLEAR} -eq 1 ]; then clear;fi

run: build
	qemu-system-i386 \
		-accel kvm \
		-cdrom hexos.iso \
		-boot d \
		-m 1G \
		-audiodev alsa,id=AlsaAudio,in.frequency=44110,out.frequency=8000 \
		-usbdevice keyboard \
		-usbdevice mouse \
		-display gtk,gl=on,window-close=on \
		-vga cirrus \
		-smbios type=0,vendor="HexBox",uefi=off
		-netdev bridge,id=n1 -device virtio-net,netdev=n1 \
		-pidfile qemu_pid.txt \
		-D qemu.log \
		-enable-kvm \
		-cpu pentiumpro

build_asm:
	i686-elf-as -o boot.o asm/boot.S

build_cc:
	g++ -c -o main.o src/main.cpp ${CXXFLAGS}
	g++ -c -o vheap.o src/vheap.cpp ${CXXFLAGS}
	g++ -c -o oop.o src/oop/oop.cpp ${CXXFLAGS}
	g++ -c -o object.o src/oop/object.cpp ${CXXFLAGS}
	g++ -c -o primitives.o src/oop/primitives.cpp ${CXXFLAGS}
	g++ -c -o string.o src/oop/list.cpp ${CXXFLAGS}

build: build_asm build_cc
	i686-elf-ld -o kernel.elf ${LDFLAGS} *o
	mkdir -p isodir/boot/grub isodir/sys
	cp grub.cfg isodir/boot/grub/grub.cfg
	cp kernel.elf isodir/sys/kernel.elf
	grub-mkrescue -o hexos.iso isodir

clean:
	rm -f *.o
