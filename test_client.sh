#!/bin/bash

# Check if filenames.txt exists
if [ ! -f filenames.txt ]; then
    echo "filenames.txt not found!"
    exit 1
fi

# Set up the host and port for the TCP requests
HOST="localhost"
PORT=8080

# Read each filename from filenames.txt and make a TCP request
while IFS= read -r filename; do
    # Strip leading/trailing whitespace and remove newlines
    filename=$(echo "$filename" | xargs | tr -d '\n')

    if [ -n "$filename" ]; then
        echo "Sending filename: $filename"
        # Send filename over TCP and print the response
        response=$(echo -n "$filename" | nc $HOST $PORT)
        echo "Response: $response"
    fi
done < filenames.txt
