cmake_minimum_required(VERSION 3.16)

set(ARCH "i386")

include("src/arch/${ARCH}/profile.cmake")
LOAD_ARCH_PROFILE()

message(STATUS "Target Architecture: ${ARCH}")
message(STATUS "Selected Compiler: ${ARCH_C_COMPILER}")
message(STATUS "Selected C++ Compiler: ${ARCH_CXX_COMPILER}")
message(STATUS "Selected Assembler: ${ARCH_ASSEMBLER}")  
message(STATUS "Selected Linker: ${ARCH_LINKER}")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER ${ARCH_C_COMPILER})
set(CMAKE_CXX_COMPILER ${ARCH_CXX_COMPILER})

enable_language(${ARCH_ASSEMBLER})
project("TerraOS")

set(CMAKE_${ARCH_ASSEMBLER}_LINK_EXECUTABLE "${ARCH_LINKER} <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_${ARCH_ASSEMBLER}_SOURCE_FILE_EXTENSIONS ${CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS} s S)
set(CMAKE_${ARCH_ASSEMBLER}_OBJECT_FORMAT elf32)

add_executable(TerraOS ${OS_ARCH_SRC})
add_custom_command(TARGET TerraOS POST_BUILD COMMAND "/bin/sh" "${PROJECT_SOURCE_DIR}/create_image.sh")

target_include_directories(TerraOS PUBLIC "src")

add_definitions(-D${ARCH_DEFINITIONS})
set(CMAKE_C_FLAGS ${ARCH_C_FLAGS})

set(CMAKE_C_LINK_EXECUTABLE "${ARCH_LINKER} <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_EXE_LINKER_FLAGS ${ARCH_LINKER_FLAGS})