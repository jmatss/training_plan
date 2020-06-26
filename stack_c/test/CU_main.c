#include "CU_main.h"

#define MAX_INPUTS       10
#define MAX_INPUT_LENGTH 50

extern tTEST_SUITE_INFO_STR const test_suite_info_str;

static int  num_of_inputs;
int         get_num_of_inputs(void) {return num_of_inputs;}
static char test_inputs[MAX_INPUTS][MAX_INPUT_LENGTH];
char*       get_input_ptr(int index) {return test_inputs[index];}

int main(int argc, char** argv)
{
    int       index;
    CU_pSuite test_suite_ptr = NULL;

    num_of_inputs = argc - 1;

    /* Get inputs */
    if (num_of_inputs > 0)
    {
        printf("\nInputs:\n");
        for (index = 1; index < argc; index++)
        {
            if (strlen(argv[index]) < MAX_INPUT_LENGTH)
            {
                strncpy(test_inputs[index-1], argv[index], MAX_INPUT_LENGTH);
                printf("  %d: %s\n", index, test_inputs[index-1]);
            }
            else
            {
                fprintf(stderr, "Maximum length for inputs is %d characters!\n", MAX_INPUT_LENGTH);
                return -1;
            }
        }
    }

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    /* Add test suite */
    test_suite_ptr = CU_add_suite(test_suite_info_str.name_ptr,
                                  test_suite_info_str.init_func_ptr,
                                  test_suite_info_str.clean_func_ptr);

    if (test_suite_ptr == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add all tests */
    for (index = 0; index < test_suite_info_str.num_of_tests; ++index)
    {
        if (CU_add_test(test_suite_ptr,
                        test_suite_info_str.test_info_ptr[index].pName,
                        test_suite_info_str.test_info_ptr[index].pTestFunc) == NULL)
        {
            CU_cleanup_registry();
            return CU_get_error();
        }
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
