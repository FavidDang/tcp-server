# Multi-Threaded C++ Server
A simple C++ server that uses pthreads to improve performance of TCP requests, in particular for many requests of large size. Developed for Linux based OS.

## Usage
After cloning the repo, run `make` to build the src files. Then from run `./bin/program` to start the server on port 8080. You can use `generate_tests.sh n` to generate n number of tests. You can run `test_client.sh` to benchmark the server with both default and multithreaded features. 
