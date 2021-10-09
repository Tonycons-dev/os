echo [TerraOS Build] Creating disk image...

cd /home/anthony/Desktop/os

# Check multiboot header
if grub-file --is-x86-multiboot build/TerraOS; then
    echo [TerraOS Build] Multiboot header found
else
    echo [TerraOS Build] No multiboot header found
    exit 1
fi

mkdir -p isodir/boot/grub
cp TerraOS isodir/boot/TerraOS.bin
cp arch/i386/grub.cfg isodir/boot/grub/grub.cfg

# Create .iso cdrom
if grub-mkrescue -o TerraOS.iso isodir; then
    echo [TerraOS Build] Created .iso image 
else
    echo [TerraOS Build] Failed creating .iso image
    exit 1
fi

# qemu-system-i386 -kernel Desktop/os/build/TerraOS
# qemu-system-i386 -cdrom TerraOS.iso

echo [TerraOS Build] Disk image created.
exit 0