#!/usr/bin/env bash

set -euo pipefail

BUILD_DIR="build"
DEBUG=0

usage() {
    cat <<EOF
Usage: ./run.sh [options]

Options:
  --debug             Start QEMU paused for GDB
  --build-dir <dir>   Build directory (default: build)
  -h, --help          Show this help
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --debug)
            DEBUG=1
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

if [[ ! -d "$BUILD_DIR" ]]; then
    echo "Build directory '$BUILD_DIR' does not exist."
    echo "Run ./build.sh first."
    exit 1
fi

if [[ $DEBUG -eq 1 ]]; then
    echo "==> Launching QEMU (waiting for GDB)..."
    cmake --build "$BUILD_DIR" --target debug
else
    echo "==> Launching QEMU..."
    cmake --build "$BUILD_DIR" --target run
fi