[![main](https://github.com/mortinger91/cpp-tcp-udp-sockets/actions/workflows/main.yml/badge.svg?branch=master)](https://github.com/mortinger91/cpp-tcp-udp-sockets/actions/workflows/main.yml)

# cpp-tcp-udp-sockets

### Easy CMake C++ project that uses sockets. Supports Linux and macOS.   

- Run as server:  
Listen on a port for incoming TCP connections.  
Prints everything it receives through the connection in the stdout.
- Run as client:  
Connect to an endpoint and port.  
Prints everything it receives through the connection in the stdout.

Requirements:
--------------
- CMake
- Clang
- LLDB
- clang-format (optional)
- VSCode 'CodeLLDB' extension (optional)

Set up project:
--------------
    ./ProjectFolder/scripts/build_cmake_debug.sh

or execute VSCode task `build_cmake_debug`.

Build and Debug:
----------------
    ./ProjectFolder/scripts/build_debug.sh

Followed by:

    lldb ./build/Debug/bin/cpp-cmake-template

or launch VSCode `DEBUG` configuration.

Run tests:
----------
    ./ProjectFolder/scripts/run_tests.sh

or execute VSCode task `run_tests`.

### Run tests in a Docker container:

    docker compose down --volumes --rmi all
    docker compose up

Build release:
--------------
    ./ProjectFolder/scripts/create_release.sh

or execute VSCode task ```create_release```.

Notes:
=======

- To add new files: 
    - create a new folder in ```ProjectFolder/src```  
    - add ```*.cpp``` and ```*.h``` files into it.
    - Remember to re-run ```build_cmake_debug```
- To add new tests: 
    - add new ```test_*.cpp``` files in ```ProjectFolder/test```.  
    - Remember to re-run ```build_cmake_debug```
