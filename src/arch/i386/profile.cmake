function(LOAD_ARCH_PROFILE)

    set(ARCH "i386" PARENT_SCOPE)
    set(ARCH_DEFINITIONS "__ARCH_I386__" PARENT_SCOPE)
    set(ARCH_C_COMPILER "/home/anthony/cross/i686-elf-tools/bin/i686-elf-gcc" PARENT_SCOPE)
    set(ARCH_C_FLAGS "-m32 -ffreestanding -O2 -nostdlib" PARENT_SCOPE)
    set(ARCH_CXX_COMPILER "/home/anthony/cross/i686-elf-tools/bin/i686-elf-g++" PARENT_SCOPE)
    set(ARCH_LINKER "/home/anthony/cross/i686-elf-tools/bin/i686-elf-ld" PARENT_SCOPE)
    set(ARCH_ASSEMBLER "ASM_NASM" PARENT_SCOPE)
    set(ARCH_LINKER_LAYOUT "src/arch/i386/linker.ld" PARENT_SCOPE)
    set(ARCH_LINKER_FLAGS "-m elf_i386 -T/home/anthony/Desktop/os/src/arch/i386/linker.ld -nostdlib" PARENT_SCOPE)

    set(I386_BOOT_ASM "src/arch/i386/boot/boot.asm")
    file(GLOB I386_MAIN_SRC "src/arch/i386/main/*.c")
    file(GLOB I386_KERNEL_SRC "src/kernel/*.c")
    file(GLOB I386_LIBC_SRC "src/libc/src/*.c")

    set(OS_ARCH_SRC ${I386_BOOT_ASM} ${I386_MAIN_SRC} ${I386_KERNEL_SRC} 
        src/kernel/system/allocator.c 
        src/kernel/system/heap/kpool.c
        src/kernel/system/heap/kheap.c
        ${I386_LIBC_SRC} PARENT_SCOPE)

endfunction(LOAD_ARCH_PROFILE)