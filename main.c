#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manager.h"
#include "tests.h"

int main()
{
    run_init_tests();
    run_malloc_tests();
    run_free_tests();
    run_write_tests();
    run_read_tests();

 //   custom_test();


  //  run_load_tests();


    return 0;
}
