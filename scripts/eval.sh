#!/bin/bash
set -e

ROOT=$(basename $(pwd))

if ./scripts/build.sh -DCMAKE_BUILD_TYPE=Release ; then
    echo "Build successful"
else
    echo "Fix build errors above"
    exit 1
fi

cd build

# Running /tests
echo "Running tests..."
if make test; then
    echo "Tests passed"
    echo "Recording execution time..."

    echo "selection-sort-int-eval" > results.txt
    echo "======================" >> results.txt
    ./eval/selection-sort-int-eval $@ | tee -a results.txt

else
    echo "Tests failed"
    echo "SKIPPED: evaluation"

fi
