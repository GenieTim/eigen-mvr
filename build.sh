#!/usr/bin/env bash

cd "$(dirname "$0")" || exit 1

mkdir -p build
cd build || exit 2
cmake .. || exit 3
cmake --build . || exit 4
