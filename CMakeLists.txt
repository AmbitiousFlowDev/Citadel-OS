cmake_minimum_required(VERSION 3.25)

project(CitadelOS LANGUAGES C ASM_NASM)

enable_language(ASM_NASM)

set(CMAKE_C_STANDARD 23)

add_executable(kernel.elf
    src/kernel.c
    src/boot.asm
)

target_compile_options(kernel.elf PRIVATE
    $<$<COMPILE_LANGUAGE:C>:
        -ffreestanding
        -fno-stack-protector
        -fno-pic
        -fno-pie
        -m64
        -mcmodel=kernel
        -Wall
        -Wextra
    >
)

target_link_options(kernel.elf PRIVATE
    -nostdlib
    -static
    -T${CMAKE_SOURCE_DIR}/linker.ld
)

set_target_properties(kernel.elf PROPERTIES
    OUTPUT_NAME kernel
    SUFFIX .elf
)

# -------------------------------------------------
# ISO directories
# -------------------------------------------------

set(ISO_DIR ${CMAKE_BINARY_DIR}/iso)

# -------------------------------------------------
# Build ISO
# -------------------------------------------------

add_custom_target(iso ALL

    COMMAND ${CMAKE_COMMAND} -E rm -rf ${ISO_DIR}

    COMMAND ${CMAKE_COMMAND} -E make_directory
            ${ISO_DIR}/boot

    COMMAND ${CMAKE_COMMAND} -E make_directory
            ${ISO_DIR}/EFI/BOOT

    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:kernel.elf>
            ${ISO_DIR}/boot/kernel.elf

    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/limine.conf
            ${ISO_DIR}/boot/

    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/limine/limine-bios.sys
            ${ISO_DIR}/boot/

    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/limine/BOOTX64.EFI
            ${ISO_DIR}/EFI/BOOT/

    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/limine/BOOTIA32.EFI
            ${ISO_DIR}/EFI/BOOT/

    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/limine/limine-bios-cd.bin
            ${ISO_DIR}/

    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/limine/limine-uefi-cd.bin
            ${ISO_DIR}/

    COMMAND xorriso
        -as mkisofs
        -R
        -J
        -b limine-bios-cd.bin
        -no-emul-boot
        -boot-load-size 4
        -boot-info-table
        --efi-boot limine-uefi-cd.bin
        -efi-boot-part
        --efi-boot-image
        --protective-msdos-label
        ${ISO_DIR}
        -o ${CMAKE_BINARY_DIR}/Citadel.iso

    COMMAND
        ${CMAKE_SOURCE_DIR}/limine/limine
        bios-install
        ${CMAKE_BINARY_DIR}/Citadel.iso

    DEPENDS kernel.elf
)

find_program(QEMU_EXECUTABLE qemu-system-x86_64)

if(QEMU_EXECUTABLE)

add_custom_target(run

    COMMAND
        ${QEMU_EXECUTABLE}
        -cdrom ${CMAKE_BINARY_DIR}/Citadel.iso
        -m 512M
        -serial stdio

    DEPENDS iso

)

endif()

add_custom_target(debug

    COMMAND
        ${QEMU_EXECUTABLE}
        -cdrom ${CMAKE_BINARY_DIR}/Citadel.iso
        -m 512M
        -s
        -S

    DEPENDS iso
)