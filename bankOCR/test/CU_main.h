/* Preprocessor directives to avoid multiple includes:                      */
#ifndef _CU_MAIN_H
#define _CU_MAIN_H

/****************************************************************************/
/* Include files:                                                           */
#include "CUnit/Basic.h"
#include <stdio.h>
#include <string.h>

//! Returns number of elements in array.
#define NUM_OF_ELEM(x) (sizeof(x) / sizeof((x)[0]))

//! Generates start od test table
#define TEST_TABLE_START \
static tTEST_INFO_STR test_info_astr[] = \
{

//! Generates end of test table
#define TEST_TABLE_END };

//! Generates a test table entry
#define TEST_TABLE_ENTRY(func) {#func, func},

//! Generates the test suite definition
#define INIT_TEST_SUITE(name, init_func, clean_func) \
tTEST_SUITE_INFO_STR const test_suite_info_str = \
{ \
    name, \
    init_func, \
    clean_func, \
    NUM_OF_ELEM(test_info_astr), \
    test_info_astr \
};

//! @name Redefinition of CUnit types
// @{
typedef CU_TestInfo       tTEST_INFO_STR;
typedef CU_InitializeFunc tTEST_INITIALIZE_PF; 
typedef CU_CleanupFunc    tTEST_CLEAN_UP_PF;
// @}

//! Test suite definition struct
typedef struct
{
    const char*         name_ptr;       //!< Test suite name
    tTEST_INITIALIZE_PF init_func_ptr;  //!< Pointer to init function
    tTEST_CLEAN_UP_PF   clean_func_ptr; //!< Pointer to clean function
    int                 num_of_tests;   //!< Number of tests
    tTEST_INFO_STR*     test_info_ptr;  //!< Pointer to test table
} tTEST_SUITE_INFO_STR;

#endif /* _CU_MAIN_H */
