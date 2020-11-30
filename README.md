# PipeSim | A MIPS-Based Pipelined Simulator
PipeSim is a A MIPS-based modular simulator with pipelining, stalling, and forwarding implemented.

## Status
Branch / Compiler | clang-5.0,  gcc-4.8.4, Xcode-9.1
------------------| --------------------------------
master | [![Build Status](https://travis-ci.com/jaller200/comp4300-project3.svg?token=4VsERWCxvrdVz6KFp1Zi&branch=master)](https://travis-ci.com/jaller200/comp4300-project3)
develop | [![Build Status](https://travis-ci.com/jaller200/comp4300-project3.svg?token=4VsERWCxvrdVz6KFp1Zi&branch=dev)](https://travis-ci.com/jaller200/comp4300-project3)

## Overview
This project is a continuation of the previous project that builds on it and adds pipelining stages to the GPR-based MIPS simulator.

My goals for the structure of this are three-fold:

* **Simple** - _I want to keep the design as easy to understand as possible_
* **Modular** - _I want developers to find it flexible and adaptable for their needs_
* **Testable** - _I want the code to be build with confidence through rigorous unit and integration testing_

Most of the project is implemented as a shared library, with the final product being a standalone application stored in the `app` folder.

More details to come later...

## Requirements
**Build Tools**: PipeSim requires CMake 2.8 and up.
* _CMake 2.8+_

**Compiler**: PipeSim requires C++11 and thus a compiler compatible with it. The program has been tested on the following compilers:

* _clang-5.0.0 on Ubuntu 14.04_
* _g++-4.8.4 on Ubuntu 14.04_
* _AppleClang-9.1.0 on macOS_

In addition, I have manually tested it on the following compilers (academic-related):

* _g++\-4.8.5 on CentOS 7_
* _Apple Clang 11.0.0 (clang-1100.0.33.17) on macOS Mojave_

## Build Instructions
Download the current version and unpack it in a directory of choice. Inside that directory, run the following command:

```
./scripts/build.sh
./scripts/test.sh
```

This will compile the library, application, and tests binaries and run the validation tests. The outputs will be stored in the following folders:

* **./bin**: The binaries for the pipeSim application and tests
* **./lib**: The shared library containing most of the simulator code

To clean up the project, just run the following:

```
./scripts/clean.sh
```

_NOTE: Run these scripts from the top-level directory. They will not work if you run them from inside the scripts folder._

## Execution Instructions
The main executable is built into the `bin` folder. The simulator can be run as follows:

```
./bin/pipeSim <path/to/file.s>
```

If you would like to debug the program, pass the debug flag (`--debug` / `-d`) on the command line, as so:

```
./bin/pipeSim <path/to/file.s> --debug
./bin/pipeSim <path/to/file.s> -d
```

## Author & Copyright
This program was created by Jonathan Hart (c) 2020. All Rights Reserved.

This code is currently not authorised for others to modify or change it in any way, nor use it without my express permission. Once the class has concluded, it will become public and licensed under the MIT license.

This project also uses Catch as the testing framework, which is licensed under the Boost License 1.0.

## Additional Notes
Auburn Student ID:  jth0069