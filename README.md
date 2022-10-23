# Introduction

The Robot Swarm Simulation Program builds a virtual phycical world, in which multiple robots consisting of a robot swarm could  automatically move and reach the targets that had been already sighned to each robot. 

The program is going to enable two basic methods, which are the task allcoation and the path planning. These methods are popular in the study of the robot swarm. 

The task allocation is a method that allocates targets to robots. The path planning is a method that generates path for the robot's movement. 

# Installation Guide

* Download the program to a location of your choice.  For illustration *only*, this guide will assume it’s been unpacked in a directory named `/path/to`, so that the Robot Swarm Simulation Program source package sits in a subdirectory. Denote the Robot Swarm Simulation Program by RSSP.

```shell
\path\to\RSSP
```

* We refer to this directory as the *source directory*. The next step is to create a directory in which to configure and run the build and store the build products. This directory could either be inside or alongside the source directory. In this guide, we create this *build directory* inside our source directory:
```shell
$ cd /path/to/RSSP
$ mkdir build
$ ls
RSSP-source-files  build
```
* We now change to this *build directory* and run CMake to generate the Makefiles needed to build the RSSP application. 

```shell
$ cd /path/to/RSSP/build
$ rm -r *
$ cmake ..
-- The C compiler identification is GNU 9.4.0
-- The CXX compiler identification is GNU 9.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/pascal/workshop-2022/virtual_robot_swarms_simulation_version3/build
$ make
Scanning dependencies of target RobotSwarmManager
[  6%] Building CXX object CMakeFiles/RobotSwarmManager.dir/src/AGVUnit.cpp.o
[ 13%] Building CXX object CMakeFiles/RobotSwarmManager.dir/src/AbstractRobotUnit.cpp.o
[ 20%] Building CXX object CMakeFiles/RobotSwarmManager.dir/src/AbstractTargetUnit.cpp.o
[ 26%] Building CXX object CMakeFiles/RobotSwarmManager.dir/src/AbstractTaskUnit.cpp.o
[ 33%] Building CXX object CMakeFiles/RobotSwarmManager.dir/src/Algorithm.cpp.o
[ 40%] Building CXX object CMakeFiles/RobotSwarmManager.dir/src/BasicDecisionMaking.cpp.o
[ 46%] Building CXX object CMakeFiles/RobotSwarmManager.dir/src/BasicPhysicalEngine.cpp.o
[ 53%] Building CXX object CMakeFiles/RobotSwarmManager.dir/src/CNCUnit.cpp.o
[ 60%] Building CXX object CMakeFiles/RobotSwarmManager.dir/src/DataProcessTool.cpp.o
[ 66%] Building CXX object CMakeFiles/RobotSwarmManager.dir/src/DecisionMaking.cpp.o
[ 73%] Building CXX object CMakeFiles/RobotSwarmManager.dir/src/LoadingTaskUnit.cpp.o
[ 80%] Building CXX object CMakeFiles/RobotSwarmManager.dir/src/PhysicalEngine.cpp.o
[ 86%] Linking CXX static library libRobotSwarmManager.a
[ 86%] Built target RobotSwarmManager
Scanning dependencies of target main
[ 93%] Building CXX object CMakeFiles/main.dir/main.cpp.o
[100%] Linking CXX executable main
[100%] Built target main
$ ls
CMakeCache.txt  CMakeFiles  cmake_install.cmake  libRobotSwarmManager.a  main  Makefile
$ ./main
```







