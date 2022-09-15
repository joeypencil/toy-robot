# toy-robot
This is my solution to the Toy Robot code challenge.

## Problem description and requirements

The application is a simulation of a toy robot moving on a square table top, of dimensions 5 units x 5 units. There are no other obstructions on the table surface. The robot is free to roam around the surface of the table, but must be prevented from falling to destruction. Any movement that would result in the robot falling from the table must be prevented, however further valid movement commands must still be allowed.

Create a **console application** that can read in commands of the following form -
```
PLACE X,Y,F
MOVE
LEFT
RIGHT
REPORT
```

`PLACE` will put the toy robot on the table in position `X,Y` and facing `NORTH`, `SOUTH`, `EAST` or `WEST`. The origin (0,0) can be considered to be the SOUTH WEST most corner. It is required that the first command to the robot is a `PLACE` command, after that, any sequence of commands may be issued, in any order, including another `PLACE` command. The application should discard all commands in the sequence until a valid `PLACE` command has been executed.

`MOVE` will move the toy robot one unit forward in the direction it is currently facing.

`LEFT` and `RIGHT` will rotate the robot 90 degrees in the specified direction without changing the position of the robot.

`REPORT` will announce the `X,Y` and `F` of the robot. This can be in any form, but standard output is sufficient.

A robot that is not on the table can choose to ignore the `MOVE`, `LEFT`, `RIGHT` and `REPORT` commands. Input can be from a file or from standard input, as the developer chooses.

Provide test data to exercise the application. It is not required to provide any graphical output showing the movement of the toy robot. The application should handle error states appropriately and be robust to user input.

## Constraints

The toy robot must not fall off the table during movement. This also includes the initial placement of the toy robot. Any move that would cause the robot to fall must be ignored.

## Example input and output

```
a)----------------
PLACE 0,0,NORTH
MOVE
REPORT
Output: 0,1,NORTH

b)----------------
PLACE 0,0,NORTH
LEFT
REPORT
Output: 0,0,WEST

c)----------------
PLACE 1,2,EAST
MOVE
MOVE
LEFT
MOVE
REPORT
Output: 3,3,NORTH
```

## Requirements in setting up the project

* C++ compiler (preferably GCC, with support for the C++17 standard or higher)
* CMake (version 3.22.1 or higher)
* Python (optional for running integration tests, version 3.9.10 or higher)
    * `robotframework` Python module

## How to setup the project

1. Setup the C++ compiler by downloading it from https://nuwen.net/mingw.html (the self-extracting archive), then follow the instructions from https://www.geeksforgeeks.org/complete-guide-to-install-c17-in-windows/ (`Install C++17 Compiler(GCC 9.2)` and `Setting up the path` sections only).
    * To check if you have done this correctly, open a command prompt and execute the command: `g++ --version`. You should see the version of the compiler displayed.

1. Download and install CMake.
    * To check if you have done this correctly, open a command prompt and execute the command `cmake --version`. You should see the version of CMake displayed.

1. Open a command prompt, and change directory to the root directory of the project.

1. Create a folder named *build* in the root directory which will contain the build files to be created by CMake, then change directory to that build folder.
    * You can create a build folder outside the root directory, but this will entail providing longer paths as argument when executing CMake down the line.
    
    ***NOTE: For the next instructions, it is assumed that you created the build folder in the root directory.***

1. Generate the build files by executing the following command: `cmake -S ../ -B .`
    * If you created the build folder outside the root directory, you'll have to provide the full path to the root directory as argument for `-S`, and the full path to your build folder as argument for `-B`.

1. Build the program and unit test by executing the following command: `cmake --build . --config Release`.
    * If you created the build folder outside the root directory, you'll have to provide the full path to your build folder as argument for `--build`.

1. The program can be found inside the build directory's *Release* folder (`toy_robot.exe`). The unit test can be found inside the build directory's *test/Release* folder (`toy_robot_unit_test.exe`).

## Executing the program

If the program is executed without any arguments, it will enter interactive mode, where commands to the robot can be entered one at a time. The program will end when an empty command is issued.

The program can be executed with one argument, which would be the full path to a file containing the commands the robot should execute.

## Running the tests

The unit test (`toy_robot_unit_test.exe`) is built together with the same command the program is built. It can be run as is.

To run the integration tests, a few additional setup steps must be taken.

### Setting up for and running integration tests

1. Install Python. Make sure that its location has been added to the `PATH` system environment variable.
    * To check if you have done this correctly, open a command prompt and execute the command `python --version`. You should see the version of Python displayed.

1. Install the `robotframework` Python module by executing the following command: `python -m pip install robotframework`.
    * To check if you have done this correctly, execute the command `python -m pip show robotframework`. You should see the version of `robotframework` displayed.

1. Change directory to the project's *test* directory (where the `integration_test.py` file is located), then run the following command: `python -m robot -v RELEASE_DIR:<full path to the Release folder where toy_robot.exe is located> -v TEST_DIR:<full path to the project's test directory where integration_test.py is located> integration_test.py`. ***It is crucial that the full paths be provided; relative paths won't work.***

1. You can see in the current working directory that there were 3 files generated: `log.html`, `report.html`, and `output.xml`.
    * `log.html` - contains test statistics and execution logs.
    * `report.html` - contains summary information, test statistics, and test details (where test results can be searched via tags, suites, or a string pattern).
    * `output.xml` - contains details concerning the test runs in XML format.