#!/bin/bash

# Check if a number is passed as an argument
if [ -z "$1" ]; then
    echo "Usage: $0 <number_of_tests>"
    exit 1
fi

# Number of test files to generate
NUM_TESTS=$1

# Directory for test files
TEST_DIR="tests"

# Size in bytes (8MB = 8 * 1024 * 1024 = 8388608 bytes)
SIZE=8388608

# Create the tests directory if it doesn't exist
mkdir -p $TEST_DIR

# Loop to generate the specified number of test files
for ((i=1; i<=NUM_TESTS; i++))
do
    FILENAME="$TEST_DIR/testfile_$i.txt"
    < /dev/urandom tr -dc 'A-Za-z0-9' | head -c $SIZE > "$FILENAME"
    echo "Generated file '$FILENAME' of size 8MB"
done

echo "$NUM_TESTS test files created in the '$TEST_DIR' directory."
