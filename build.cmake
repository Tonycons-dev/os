function(FLAT_BUILD)

    set(ARCH "i386")
    set(ARCH_DEFINITIONS "-D__X86_64__ -D__ARCH_I386__")
    set(ARCH_C_COMPILER "/home/anthony/cross/i686-elf-tools/bin/i686-elf-gcc")
    set(ARCH_CXX_COMPILER "/home/anthony/cross/i686-elf-tools/bin/i686-elf-g++")
    set(ARCH_ASSEMBLER "ASM-NASM")
    set(ARCH_ASSEMBLER_MODULE_PATH "cmake-modules/nasm")
    set(ARCH_CRTBEGIN_LOCATION "")
    set(ARCH_CRTBEGIN_LOCATION "")
    set(ARCH_LINKER_LAYOUT "src/arch/i386/linker.ld")
    set(ARCH_LINKER_FLAGS "")

    set(CMAKE_C_COMPILER ${ARCH_C_COMPILER})
    set(CMAKE_CXX_COMPILER ${ARCH_CXX_COMPILER})
    set(CMAKE_ASM-NASM_COMPILER "/usr/bin/nasm")

    set(CMAKE_DEFAULT_MODULE_PATH CMAKE_MODULE_PATH)
    set(CMAKE_MODULE_PATH "cmake-modules")

    enable_language(${ARCH_ASSEMBLER})

    message(STATUS "Target Architecture: ${ARCH}")
    message(STATUS "Selected Compiler: ${ARCH_C_COMPILER}")
    message(STATUS "Selected C++ Compiler: ${ARCH_CXX_COMPILER}")
    message(STATUS "Selected Assembler: ${ARCH_ASSEMBLER}")    

    project("TerraOS")

    message(STATUS "Building kernel...")

    set(OS_ARCH_CORE_SRC "src/arch/i386/core/boot.s")
    file(GLOB OS_ARCH_MAIN_SRC "src/arch/i386/main/*.c")
    file(GLOB OS_ARCH_KERNEL_SRC "src/kernel/*.c")

    add_executable(TerraOS ${OS_ARCH_CORE_SRC} ${OS_ARCH_MAIN_SRC} ${OS_ARCH_KERNEL_SRC})

    target_include_directories(TerraOS PUBLIC "kernel")
    target_compile_definitions(TerraOS PUBLIC "${ARCH_DEFINITIONS}")

    target_link_options(TerraOS PUBLIC "-T ${ARCH_LINKER_LAYOUT}")
    target_link_options(TerraOS PUBLIC "-N ${ARCH_LINKER_FLAGS}")

    target_compile_options(TerraOS PUBLIC "-O2")
    target_compile_options(TerraOS PUBLIC "-nostdlib")

    message(STATUS "Done building kernel.")

endfunction(FLAT_BUILD)




function(SELECT_COMPILERS)

    message(STATUS "Target Architecture: ${ARCH}")

    include("src/arch/${ARCH}/profile.cmake")
    LOAD_ARCH_PROFILE()

    set(CMAKE_C_COMPILER ${ARCH_C_COMPILER})
    set(CMAKE_CXX_COMPILER ${ARCH_CXX_COMPILER})

    set(CMAKE_DEFAULT_MODULE_PATH CMAKE_MODULE_PATH)
    set(CMAKE_MODULE_PATH "cmake-modules")

    enable_language(${ARCH_ASSEMBLER})

    set(CMAKE_MODULE_PATH CMAKE_DEFAULT_MODULE_PATH)

    message(STATUS "Selected Compiler: ${ARCH_C_COMPILER}")
    message(STATUS "Selected C++ Compiler: ${ARCH_CXX_COMPILER}")
    message(STATUS "Selected Assembler: ${ARCH_ASSEMBLER}")

endfunction(SELECT_COMPILERS)


function(BUILD_KERNEL)

    message(STATUS "Building kernel...")

    include("src/arch/${ARCH}/profile.cmake")
    COMPILE_ARCH_PROFILE()

    target_include_directories(TerraOS PUBLIC "kernel")
    target_compile_definitions(TerraOS PUBLIC ${ARCH_DEFINITIONS})

    target_link_options(TerraOS PUBLIC "-T ${ARCH_LINKER_LAYOUT}")
    target_link_options(TerraOS PUBLIC "-N ${ARCH_LINKER_FLAGS}")

    target_compile_options(TerraOS PUBLIC "-O2")
    target_compile_options(TerraOS PUBLIC "-nostdlib")
    
endfunction(BUILD_KERNEL)