# PipeSim | A MIPS-Based Pipelined Simulator
PipeSim is a A MIPS-based modular simulator with pipelining, stalling, and forwarding implemented.

## Overview
This project is a continuation of the previous project that builds on it and adds pipelining stages to the GPR-based MIPS simulator.

My goals for the structure of this are three-fold:

* **Simple** - _I want to keep the design as easy to understand as possible_
* **Modular** - _I want developers to find it flexible and adaptable for their needs_
* **Testable** - _I want the code to be build with confidence through rigorous unit and integration testing_

This project is currently implemented as a binary executable, although my plan is to move the bulk of it to a static library in the future.

More details to come later...

## Requirements
**Compiler**: PipeSim requires C++11 and thus a compiler compatible with it. The program has been tested on the following compilers:

* g++-4.8.5 on CentOS 7
* Apple Clang 11.0.0 (clang-1100.0.33.17) on macOS Mojave

## Build Instructions
_Aside: Due to constraints from the school's Linux servers with an outdated CMake version (2.8), this project is currently built via Make. CMake 3.1+ will be used in the future._

Download the current version and unpack it in a directory of choice. Inside that directory, run the following commands:

```
make test
make
```

This will compile and run all validation tests, and then make the final project.

## Execution Instructions
The main executable is built into the `bin` folder. The simulator can be run as follows:

```
./pipeSim <path/to/file.s>
```

## Author & Copyright
This program was created by Jonathan Hart (c) 2020. All Rights Reserved.

This code is currently not authorised for others to modify or change it in any way, nor use it without my express permission. Once the class has concluded, it will become public and licensed under the MIT license.

This project also uses Catch as the testing framework, which is licensed under the Boost License 1.0.

## Additional Notes
Auburn Student ID:  jth0069