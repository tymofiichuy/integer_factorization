cmake_minimum_required(VERSION 3.10)
project(long_arithmetic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# include_directories(${SOURCE_DIR})

set(SOURCES
    ${SOURCE_DIR}/long_arithmetic.cpp
    ${SOURCE_DIR}/digit.cpp
    ${SOURCE_DIR}/modular_arithmetic.cpp
    ${SOURCE_DIR}/operators.cpp
)

add_library(long_modular_arithmetic STATIC ${SOURCES})

target_include_directories(long_modular_arithmetic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)