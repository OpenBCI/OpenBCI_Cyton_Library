cmake_minimum_required(VERSION 3.4)
project(OpenBCI_32bit)

include_directories("/Users/ajk/Documents/Arduino/hardware/chipkit-core/pic32/compiler/pic32-tools/pic32mx/include")
include_directories("/Users/ajk/Documents/Arduino/hardware/chipkit-core/pic32/cores/pic32")
include_directories("/Users/ajk/Documents/Arduino/hardware/chipkit-core/pic32/libraries/DSPI")
include_directories("/Users/ajk/Documents/Arduino/hardware/chipkit-core/pic32/variants/openbci")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    OpenBCI_32bit.cpp
    OpenBCI_32bit.h
    OpenBCI_32bit_Definitions.h)

add_executable(OpenBCI_32bit ${SOURCE_FILES})