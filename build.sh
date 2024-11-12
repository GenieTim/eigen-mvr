#!/usr/bin/env bash

cd "$(dirname "$0")" || exit 1

mkdir -p build
cd build || exit 2
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo || exit 3
cmake --build . || exit 4
