cmake_minimum_required(VERSION 3.12)
project(bankOCR)

set(TARGET test_runner)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(SRC_FILES converter.c)
list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR})

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test/)
set(CUNIT_DIR ${TEST_DIR}cunit)
set(TEST_FILES CU_main.c tests.c)
list(TRANSFORM TEST_FILES PREPEND ${TEST_DIR})

add_executable(${TARGET} ${SRC_FILES} ${TEST_FILES})

target_include_directories(${TARGET} PRIVATE ${SRC_DIR})
target_include_directories(${TARGET} PRIVATE ${TEST_DIR})
target_include_directories(${TARGET} PRIVATE ${CUNIT_DIR})

target_link_libraries(${TARGET} PRIVATE ${CUNIT_DIR}/libcunit.a)