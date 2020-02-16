# Lecture 9 Source

This project contains source code used with lecture 9 of [Advanced Embedded Software Development](https://sites.google.com/colorado.edu/ecen5013/home) at CU Boulder.

# Unit Testing
The project supports unit testing based on the [Unity](http://www.throwtheswitch.org/unity) framework.  To run locally on Ubuntu 18.04:

1. `sudo apt-get install cmake ruby` to install Unity and cmake dependencies
2. `git submodule init && git submodule update` to setup the unity submodule
3. `mkdir build && cd build && cmake ..` To setup the cmake build for your platform

Then build and run unit tests using these commands from the build directory:
1. `make` to build the unit test application.  This uses the auto-generate script through a cmake custom command
2. `./unity-test` to run unity tests
