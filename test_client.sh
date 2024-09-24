#!/bin/bash

# Check if the tests folder exists
if [ ! -d tests ]; then
    echo "tests folder not found!"
    exit 1
fi

# Set up the host and port for the TCP requests
HOST="localhost"
PORT=8080

# Function to send a TCP request and record the time
send_request() {
    local filename=$1
    # Strip leading/trailing whitespace and remove newlines
    filename=$(echo "$filename" | xargs | tr -d '\n')

    if [ -n "$filename" ]; then
        echo "Sending filename: $filename"
        # Start timer
        start_time=$(date +%s%3N)

        # Send filename over TCP and capture the response
        response=$(echo -n "$filename" | nc $HOST $PORT)

        # End timer
        end_time=$(date +%s%3N)

        # Calculate elapsed time
        elapsed_time=$((end_time - start_time))

        if [ -n "$response" ]; then
            echo "Response for $filename: Received! (received in ${elapsed_time} ms)"
        else
            echo "No response for $filename"
        fi

    fi
}

# Read each filename from the tests folder and make a TCP request asynchronously
for file in tests/*; do
    # Extract the filename only (without the folder path)
    filename=$(basename "$file")
    send_request "$filename" &
    # Sleep for a little bit to avoid overwhelming the server
    # sleep 0.25 # Adjust the sleep time as necessary (0.5 seconds here)
done

# Wait for all background jobs to finish
wait
