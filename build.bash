#!/usr/bin/env bash

set -euo pipefail

CONFIGURATION="Debug"
BUILD_DIR="build"

RUN=0
DEBUG_QEMU=0
CLEAN=0

usage() {
    cat <<EOF
Usage: ./build.sh [options]

Options:
  --debug             Build Debug (default)
  --release           Build Release
  --run               Launch QEMU after building
  --debug-qemu        Launch QEMU paused for GDB
  --clean             Remove build directory before configuring
  --build-dir <dir>   Build directory (default: build)
  -h, --help          Show this help
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --debug)
            CONFIGURATION="Debug"
            ;;
        --release)
            CONFIGURATION="Release"
            ;;
        --run)
            RUN=1
            ;;
        --debug-qemu)
            DEBUG_QEMU=1
            ;;
        --clean)
            CLEAN=1
            ;;
        --build-dir)
            BUILD_DIR="$2"
            shift
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
    shift
done

step() {
    echo
    echo "==> $1"
}

require() {
    command -v "$1" >/dev/null 2>&1 || {
        echo "Error: '$1' is not installed."
        exit 1
    }
}

require cmake
require ninja
require clang
require nasm

if [[ $CLEAN -eq 1 ]]; then
    step "Cleaning"
    rm -rf "$BUILD_DIR"
fi

step "Configuring"

cmake \
    -S . \
    -B "$BUILD_DIR" \
    -G Ninja \
    -DCMAKE_BUILD_TYPE="$CONFIGURATION" \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_ASM_NASM_COMPILER=nasm

step "Building"

cmake \
    --build "$BUILD_DIR" \
    --parallel

if [[ $RUN -eq 1 ]]; then
    step "Running"
    cmake --build "$BUILD_DIR" --target run
    exit 0
fi

if [[ $DEBUG_QEMU -eq 1 ]]; then
    step "Running (GDB)"
    cmake --build "$BUILD_DIR" --target debug
    exit 0
fi

echo
echo "Build completed successfully."
echo
echo "Artifacts:"
echo "  ELF : $BUILD_DIR/kernel.elf"
echo "  ISO : $BUILD_DIR/Citadel.iso"