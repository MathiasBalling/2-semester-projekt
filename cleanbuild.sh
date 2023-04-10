#!/bin/bash
dir="$(cd -P -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)"
cd "$dir"
mkdir -p build
cd build
rm -r ./**
cmake .. 
cmake --build .
./NBNP-Chess
