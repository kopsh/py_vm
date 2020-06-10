cmake_minimum_required(VERSION 2.8)

PROJECT(PYVM)

SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")

ADD_EXECUTABLE(pyvm main.cpp
    code/CodeObject.cpp
    code/binaryFileParser.cpp
    object/HiString.cpp
    object/HiInteger.cpp
    object/HiObject.cpp
    runtime/frameObject.cpp
    runtime/functionObject.cpp
    runtime/interpreter.cpp
    runtime/universe.cpp
    util/ArrayList.cpp
    util/Map.cpp)

INCLUDE_DIRECTORIES(./)