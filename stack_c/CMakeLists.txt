cmake_minimum_required(VERSION 3.12)
project(stack_c)

set(TARGET test_runner)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(LINN_DIR ${SRC_DIR}linn_lib)
set(SRC_FILES j_stack.c)
list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR})

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test/)
set(CUNIT_DIR ${TEST_DIR}cunit)
set(TEST_FILES CU_main.c stackTest.c j_stackTest.c l_stackTest.c)
list(TRANSFORM TEST_FILES PREPEND ${TEST_DIR})

message(${TEST_FILES})

add_executable(${TARGET} ${SRC_FILES} ${TEST_FILES})

target_include_directories(${TARGET} PRIVATE ${SRC_DIR})
target_include_directories(${TARGET} PRIVATE ${TEST_DIR})
target_include_directories(${TARGET} PRIVATE ${CUNIT_DIR})
target_include_directories(${TARGET} PRIVATE ${LINN_DIR})

target_link_libraries(${TARGET} PRIVATE ${CUNIT_DIR}/libcunit.a)
target_link_libraries(${TARGET} PRIVATE ${LINN_DIR}/libl_stack.a)