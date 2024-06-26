cmake_minimum_required(VERSION 3.28)
project(p37-sudoku-solver)
set(CMAKE_CXX_STANDARD 26)
add_executable(p37-sudoku-solver main.cpp
        dlx_solution.cpp)