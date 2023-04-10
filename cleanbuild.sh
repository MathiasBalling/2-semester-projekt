#!/bin/bash
dir="$(cd -P -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)"
cd "$dir/build"
rm -r ./**
cmake -S .. -B .
cmake --build .
./NBNP-Chess
