cmake_minimum_required(VERSION 3.10)
project(factorization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(MAIN_DIR ${CMAKE_SOURCE_DIR}/main)

set(QS_SOURCES
    ${SOURCE_DIR}/quadratic_sieve.cpp
    ${SOURCE_DIR}/tonelli_shanks.cpp
    ${SOURCE_DIR}/trial_division.cpp
    ${SOURCE_DIR}/matrix.cpp
    ${SOURCE_DIR}/f_exeption.cpp
)

set(NON_QS_SOURCES
    ${SOURCE_DIR}/trial_division.cpp
    ${SOURCE_DIR}/solovay_strassen.cpp
    ${SOURCE_DIR}/rho_pollard.cpp
)


add_subdirectory(long_modular_arithmetic)

include_directories(${SOURCE_DIR})

add_executable(td_test ${TEST_DIR}/td_test.cpp ${NON_QS_SOURCES})
add_executable(ts_test ${TEST_DIR}/ts_test.cpp ${QS_SOURCES})
add_executable(qs_test ${TEST_DIR}/qs_test.cpp ${QS_SOURCES})
add_executable(ss_test ${TEST_DIR}/ss_test.cpp ${NON_QS_SOURCES})
add_executable(rho_test ${TEST_DIR}/rho_test.cpp ${NON_QS_SOURCES})
add_executable(main ${MAIN_DIR}/main.cpp ${QS_SOURCES} ${NON_QS_SOURCES})

target_link_libraries(qs_test PRIVATE long_modular_arithmetic)
target_link_libraries(ts_test PRIVATE long_modular_arithmetic)
target_link_libraries(main PRIVATE long_modular_arithmetic)