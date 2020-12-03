# PipeSim | A MIPS-Based Pipelined Simulator
PipeSim is a A MIPS-based modular simulator with pipelining, stalling, and forwarding implemented.

## Status
Branch / Compiler | clang-(3.6/3.7),  gcc-(4.9/5.0)
------------------| --------------------------------
master | [![Build Status](https://travis-ci.com/jaller200/comp4300-project3.svg?token=4VsERWCxvrdVz6KFp1Zi&branch=master)](https://travis-ci.com/jaller200/comp4300-project3)
dev    | [![Build Status](https://travis-ci.com/jaller200/comp4300-project3.svg?token=4VsERWCxvrdVz6KFp1Zi&branch=dev)](https://travis-ci.com/jaller200/comp4300-project3)

## Overview
This project is a continuation of the previous project that builds on it and adds pipelining stages to the GPR-based MIPS simulator.

My goals for the structure of this are three-fold:

* **Simple** - _I want to keep the design as easy to understand as possible_
* **Modular** - _I want developers to find it flexible and adaptable for their needs_
* **Testable** - _I want the code to be build with confidence through rigorous unit and integration testing_

Most of the project is implemented as a shared library, with the final product being a standalone application stored in the `app` folder.

More details to come later...

_**NOTE**: Due to time constraints, testing of most handlers / parsers is incomplete. Much of the rest of the code covered._

## Requirements
**Build Tools**: PipeSim requires CMake 2.8 and up.
* _CMake 2.8+_

**Compiler**: PipeSim requires C++11 and thus a compiler compatible with it. The program has been tested on the following compilers:

* _clang-3.6 on Ubuntu 14.04_
* _clang-3.7 on Ubuntu 14.04_
* _g++-4.9.0 on Ubuntu 14.04_
* _g++-5.0.0 on Ubuntu 14.04_

In addition, I have manually tested it on the following compilers (academic-related):

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

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This project also uses Catch as the testing framework, which is licensed under the Boost License 1.0, and SpdLog, which is licensed under the MIT License.

## Additional Notes
Auburn Student ID:  jth0069

### lab3a.s
|                          |     |
|--------------------------|-----|
| Clock Cycles             | 269 |
| Total Instructions (NOP) | 166 |
| Total Instructions (All) | 269 |

### lab3b.s 
**Input: test**
|                          |     |
|--------------------------|-----|
| Clock Cycles             | 64  |
| Total Instructions (NOP) | 16  |
| Total Instructions (All) | 64  |

**Input: bob**
|                          |     |
|--------------------------|-----|
| Clock Cycles             | 52  |
| Total Instructions (NOP) | 11  |
| Total Instructions (All) | 52  |

### lab3c.s
|                          |     |
|--------------------------|-----|
| Clock Cycles             | 59  |
| Total Instructions (NOP) | 1   |
| Total Instructions (All) | 59  |