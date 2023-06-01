[![cpp-tcp-udp-server](https://github.com/mortinger91/cpp-tcp-udp-server/actions/workflows/cmake.yml/badge.svg?branch=master)](https://github.com/mortinger91/cpp-tcp-udp-server/actions/workflows/cmake.yml)

<h1>cpp-tcp-udp-server</h1>
Easy CMake C++ project that uses sockets. Supports Linux and macOS.<br>
Listen on a port (set it in the main) for a TCP connection,<br>
then prints everything it receives through the connection as hex in the stdout.<br>
<h3>My use case:</h3>
Doing networking research and using it as a code alternative to 

```Netcat``` in which I can change things, add new code, set breakpoints, etc.   
<h2>Set up project:</h2>
Execute script:

```./ProjectFolder/scripts/build_cmake.sh```<br>
or execute task "build_cmake" in VSCode.
<h2>Build and Run:</h2>
Execute script:

```./ProjectFolder/scripts/make_debug.sh```<br>
then run:<br>
```./ProjectFolder/build/debug/bin/cpp-server```<br>
or select and run a configuration in VSCode:<br>

- Debug<br>
- Release

<h2>Run tests:</h2>
Execute script:

```./ProjectFolder/scripts/run_tests.sh```<br>
or execute task "run_tests" in VSCode.

To run tests in a Docker container:<br>
```docker compose down --volumes --rmi all```<br>
```docker compose up```

<h2>Notes:</h2>

- When creating a new folder in ProjectFolder/src<br>
also add its name in ProjectFolder/src/CMakeLists.txt
- To add a new test just add a new test_***.cpp file<br>
in ProjectFolder/test.
