.PHONY: qemu debug clean

kernel.elf:
	$(MAKE) -C kernel kernel.elf
	cp kernel/kernel.elf kernel.elf

osmium.iso: kernel.elf
	rm -f iso/kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	grub-mkrescue -o osmium.iso iso

qemu: osmium.iso
	qemu-system-x86_64 -boot d -cdrom osmium.iso -m 4096

debug: osmium.iso
	qemu-system-x86_64 -boot d -cdrom osmium.iso -m 4096 -s -S

clean:
	$(MAKE) -C kernel clean
	rm -f *.iso *.elf *.sym iso/boot/*.elf