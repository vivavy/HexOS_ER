all: makepp

run:
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
		-smbios type=0,vendor="HexBox",uefi=off \
		-D qemu.log \
		-cpu pentium2 \
		-serial stdio
