cmake_minimum_required(VERSION 3.10)
project(factorization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(MAIN_DIR ${CMAKE_SOURCE_DIR}/main)

set(QS_SOURCES
    ${SOURCE_DIR}/quadratic_sieve.cpp
    ${SOURCE_DIR}/solovay_strassen.cpp
    ${SOURCE_DIR}/trial_division.cpp
    ${SOURCE_DIR}/matrix.cpp
    ${SOURCE_DIR}/f_exeption.cpp
)

set(TD_SOURCES
    ${SOURCE_DIR}/trial_division.cpp
)

add_subdirectory(long_modular_arithmetic)

include_directories(${SOURCE_DIR})

add_executable(td_test ${TEST_DIR}/td_test.cpp ${TD_SOURCES})
add_executable(qs_test ${TEST_DIR}/qs_test.cpp ${QS_SOURCES})
target_link_libraries(qs_test PRIVATE long_modular_arithmetic)