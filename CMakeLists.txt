cmake_minimum_required(VERSION 3.5)
project(factorization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(MAIN_DIR ${CMAKE_SOURCE_DIR}/main)

set(SOURCES
    ${SOURCE_DIR}/quadratic_sieve.cpp
    ${SOURCE_DIR}/rho_pollard.cpp
    ${SOURCE_DIR}/solovay_strassen.cpp
    ${SOURCE_DIR}/trial_division.cpp
)

include_directories(${SOURCE_DIR})