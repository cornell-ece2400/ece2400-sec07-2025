#!/bin/bash
set -e

ROOT=$(basename $(pwd))

mkdir -p build
cd build
cmake $1 $2 $3 $4 ..
make
echo "Build Successful"
