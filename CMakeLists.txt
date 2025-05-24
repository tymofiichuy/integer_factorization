cmake_minimum_required(VERSION 3.10)
project(factorization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(MAIN_DIR ${CMAKE_SOURCE_DIR}/main)
set(LONG_ARITHMETIC_DIR ${CMAKE_SOURCE_DIR}/long_modular_arithmetic)

set(SOURCES
    ${SOURCE_DIR}/quadratic_sieve.cpp
    ${SOURCE_DIR}/rho_pollard.cpp
    ${SOURCE_DIR}/solovay_strassen.cpp
    ${SOURCE_DIR}/trial_division.cpp
    ${SOURCE_DIR}/matrix.cpp
)

set(LONG_ARITHMETIC
    ${LONG_ARITHMETIC_DIR}/digit.cpp
    ${LONG_ARITHMETIC_DIR}/long_arithmetic.cpp
    ${LONG_ARITHMETIC_DIR}/operators.cpp
    ${LONG_ARITHMETIC_DIR}/modular_arithmetic.cpp
)

include_directories(${SOURCE_DIR})
include_directories(${LONG_ARITHMETIC_DIR})

add_executable(test ${TEST_DIR}/test.cpp ${SOURCES} ${LONG_ARITHMETIC})