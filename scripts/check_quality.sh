#!/bin/bash

# Останавливать скрипт при любой ошибке
set -e

# Определяем корень проекта
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$PROJECT_ROOT"

check_tool() {
    if ! command -v "$1" &> /dev/null; then
        echo "Error: Required tool '$1' is not installed." >&2
        exit 1
    fi
}

echo "Checking required tools..."
check_tool cmake
check_tool clang-format
check_tool cppcheck
check_tool clang-tidy

BUILD_DIR="build"
if [ -d "$BUILD_DIR" ]; then
    rm -rf "${BUILD_DIR:?}"/*
else
    mkdir "$BUILD_DIR"
fi

echo "[1/6] Configuring project..."
cmake -S . -B "$BUILD_DIR"

echo "[2/6] Building project..."
cmake --build "$BUILD_DIR"

echo "[3/6] Checking formatting..."
clang-format --dry-run --Werror src/*.cpp include/*.hpp

echo "[4/6] Running Cppcheck..."
cppcheck --enable=all --language=c++ --std=c++20 --error-exitcode=1 src/ include/

echo "[5/6] Running Clang-Tidy..."
clang-tidy -p="$BUILD_DIR" src/*.cpp

echo "[6/6] Running application checks..."
./"$BUILD_DIR"/oop_assets

echo -e "\nAll quality checks passed."
exit 0