#!/bin/bash
set -e

ROOT=$(basename $(pwd))

if ./scripts/build.sh ; then
    echo "Build successful"
else
    echo "Fix build errors above"
    exit 1
fi

cd build

# Running /tests
echo "Running tests..."
if make test; then
    echo "Tests successful"
else
    echo "Tests failed"
fi
