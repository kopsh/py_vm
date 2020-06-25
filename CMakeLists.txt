cmake_minimum_required(VERSION 2.8)

PROJECT(PYVM)

SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")

ADD_EXECUTABLE(pyvm main.cpp
    code/CodeObject.cpp
    code/binaryFileParser.cpp
    object/HiDict.cpp
    object/HiInteger.cpp
    object/HiList.cpp
    object/HiObject.cpp
    object/HiString.cpp
    object/Klass.cpp
    runtime/cellObject.cpp
    runtime/frameObject.cpp
    runtime/IntegerTable.cpp
    runtime/functionObject.cpp
    runtime/interpreter.cpp
    runtime/universe.cpp
    util/ArrayList.cpp
    util/Map.cpp)

INCLUDE_DIRECTORIES(./)