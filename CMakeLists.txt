cmake_minimum_required(VERSION 3.10)
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
    ${SOURCE_DIR}/matrix.cpp
    ${SOURCE_DIR}/f_exeption.cpp
)

add_subdirectory(long_modular_arithmetic)

include_directories(${SOURCE_DIR})

add_executable(test ${TEST_DIR}/test.cpp ${SOURCES})

target_link_libraries(test PRIVATE long_modular_arithmetic)