#!/bin/bash
dir="$(cd -P -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)"
cd "$dir/build"
cmake --build .
./NBNP-Chess