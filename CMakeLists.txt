cmake_minimum_required(VERSION 3.29)
project(T3)

set(CMAKE_CXX_STANDARD 20)

add_executable(T3 main.cpp
        Register.h
        Register.cpp
        Memory.h)
