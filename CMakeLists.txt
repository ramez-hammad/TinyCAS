cmake_minimum_required(VERSION 3.31)

project(TinyCAS)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/interpreter)

add_executable(Lexer
        src/interpreter/lexer.cpp
)
