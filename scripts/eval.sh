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

    echo "list-int-contains-eval 100" > results.txt
    echo "======================" >> results.txt
    ./eval/list-int-contains-eval 100 >> results.txt

    echo "list-int-push-back-eval 100" >> results.txt
    echo "======================" >> results.txt
    ./eval/list-int-push-back-eval 100 >> results.txt

    echo "vector-int-contains-eval 100" >> results.txt
    echo "======================" >> results.txt
    ./eval/vector-int-contains-eval 100 >> results.txt

    echo "vector-int-push-back-v1-eval 100" >> results.txt
    echo "======================" >> results.txt
    ./eval/vector-int-push-back-v1-eval 100 >> results.txt

    echo "vector-int-push-back-v2-eval 100" >> results.txt
    echo "======================" >> results.txt
    ./eval/vector-int-push-back-v2-eval 100 >> results.txt

    cat results.txt
else
    echo "Tests failed"
    echo "SKIPPED: evaluation"

fi
