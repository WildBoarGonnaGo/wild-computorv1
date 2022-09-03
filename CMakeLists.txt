cmake_minimum_required(VERSION 3.20)
project(wild_computorv1)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra -Werror)

include_directories(.)

add_executable(wild_computorv1
        computor.cpp
        computor.h
        main.cpp)
