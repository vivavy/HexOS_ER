all: makepp

makepp:
	python3 scripts/make++.py

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
		-cpu pentiumpro \
		-serial stdio
