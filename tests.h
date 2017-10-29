#ifndef MEMORY_TESTS_H
#define MEMORY_TESTS_H

#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#include "manager.h"

void run_init_tests();
void init_test_1();
void init_test_2();
void init_test_3();

void run_malloc_tests();
void malloc_test_1();
void malloc_test_2();
void malloc_test_3();
void malloc_test_4();
void malloc_test_5();

void run_free_tests();
void free_test_1();
void free_test_2();
void free_test_3();

void run_write_tests();
void write_test_1();
void write_test_2();
void write_test_3();
void write_test_4();
void write_test_5();
void write_test_6();

void run_read_tests();
void read_test_1();
void read_test_2();
void read_test_3();
void read_test_4();
void read_test_5();
void read_test_6();

void custom_test();

void run_load_tests();
void load_test(int size);

#endif //MEMORY_TESTS_H
