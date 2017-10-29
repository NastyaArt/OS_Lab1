#include "tests.h"

void run_init_tests()
{
    printf("\nInit tests...\n");

    init_test_incorrect_data();
    init_test_out_of_size();
    init_test_success();

    printf("\nInit tests passed successfully!\n");
}

void init_test_incorrect_data()          //некорректные данные
{
    assert(_init(1, -5)==-1);
}

void init_test_out_of_size()          //попытка выделить память больше допустимого
{
    assert(_init(1, 270)==-1);
}

void init_test_success()          //успешная инициализация
{
    assert(_init(1, 180)==0);
}

void run_malloc_tests()
{
    printf("\nMalloc tests...\n");

    malloc_test_1();
    malloc_test_2();
    malloc_test_3();
    malloc_test_4();
    malloc_test_5();

    printf("\nMalloc tests passed successfully!\n");
}

void malloc_test_out_of_memory()          //блок больше всей памяти
{
    _init(1, 100);
    VA ptr="00000000";

    assert(_malloc(&ptr, 110)==-2);
}

void malloc_test_incorrect_address()          //некорректный адрес
{
    _init(1, 100);
    VA ptr="00test70";

    assert(_malloc(&ptr, 10)==-1);
}

void malloc_test_success()          //успешное добавление блока
{
    _init(1, 100);
    VA ptr="00000000";

    assert(_malloc(&ptr, 40)==0);
}

void malloc_test_memory_lack()          //нехватка памяти
{
    _init(1, 100);
    VA ptr1="00000000";
    VA ptr2="00000001";
    VA ptr3="00000010";
    _malloc(&ptr1, 40);
    _malloc(&ptr2, 40);

    assert(_malloc(&ptr3, 40)==-2);
}

void malloc_test_not_available_address()          //адрес уже занят
{
    _init(1, 100);
    VA ptr1="00000000";
    VA ptr2="00000000";
    _malloc(&ptr1, 40);

    assert(_malloc(&ptr2, 60)==-1);
}

void run_free_tests()
{
    printf("\nFree tests...\n");

    free_test_1();
    free_test_2();
    free_test_3();

    printf("\nFree tests passed successfully!\n");
}

void free_test_incorrect_address()          //некорректный адрес
{
    _init(1, 100);
    VA ptr="00000000";
    VA ptr1="00test70";
    _malloc(&ptr, 40);

    assert(_free(ptr1)==-1);
}

void free_test_success()          //успешное удаление блока
{
    _init(1, 100);
    VA ptr="00000000";
    _malloc(&ptr, 40);

    assert(_free(ptr)==0);
}

void free_test_address_is_not_exist()          //адрес не указывает ни на один блок
{
    _init(1, 100);
    VA ptr="00000000";
    VA ptr1="00000001";
    _malloc(&ptr, 40);

    assert(_free(ptr1)==-1);
}

void run_write_tests()
{
    printf("\nWrite tests...\n");

    write_test_1();
    write_test_2();
    write_test_3();
    write_test_4();
    write_test_5();
    write_test_6();

    printf("\nWrite tests passed successfully!\n");
}

void write_test_incorrect_address()          //некорректный адрес
{
    _init(1, 15);
    VA ptr="00000000";
    VA ptr1="000test70";
    _malloc(&ptr, 6);

    assert(_write(ptr1, "string", 6)==-1);
}

void write_test_address_is_not_exist()          //адрес не указывает ни на один блок
{
    _init(1, 15);
    VA ptr="00000000";
    VA ptr1="00000001";
    _malloc(&ptr, 6);

    assert(_write(ptr1, "string", 6)==-1);
}

void write_test_incorrect_size_of_buffer()          //размер буфера не соответствует буферу
{
    _init(1, 15);
    VA ptr="00000000";
    _malloc(&ptr, 6);

    assert(_write(ptr, "string", 4)==-1);
}

void write_test_out_of_block()          //размер буфера больше размера блока
{
    _init(1, 15);
    VA ptr="00000000";
    _malloc(&ptr, 4);

    assert(_write(ptr, "string", 6)==-2);
}

void write_test_success()          //успешная запись информации в блок
{
    _init(1, 15);
    VA ptr="00000000";
    _malloc(&ptr, 5);

    assert(_write(ptr, "first", 5)==0);
}

void write_test_block_is_full()          //попытка записи в уже заполненный блок
{
    _init(1, 15);
    VA ptr="00000000";
    _malloc(&ptr, 5);
    _write(ptr, "first", 5);

    assert(_write(ptr, "secnd", 5)==-1);
}


void run_read_tests()
{
    printf("\nRead tests...\n");

    read_test_1();
    read_test_2();
    read_test_3();
    read_test_4();
    read_test_5();
    read_test_6();

    printf("\nRead tests passed successfully!\n");
}

void read_test_incorrest_address()          //некорректный адрес
{
    _init(1, 15);
    VA ptr="00000000";
    VA ptr1="000test70";
    _malloc(&ptr, 5);
    _write(ptr, "first", 5);
    const int szBuf=5;
    char* ptrBuf=calloc(szBuf, sizeof(char));

    assert(_read(ptr1, ptrBuf, szBuf)==-1);
}

void read_test_address_is_not_exist()          //адрес не указывает ни на один блок
{
    _init(1, 15);
    VA ptr="00000000";
    VA ptr1="00000001";
    _malloc(&ptr, 5);
    _write(ptr, "first", 5);
    const int szBuf=5;
    char* ptrBuf=calloc(szBuf, sizeof(char));

    assert(_read(ptr1, ptrBuf, szBuf)==-1);
}

void read_test_incorrect_size_of_buffer()          //некорректный размер буфера
{
    _init(1, 15);
    VA ptr="00000000";
    _malloc(&ptr, 5);
    _write(ptr, "first", 5);
    const int szBuf=5;
    char* ptrBuf=calloc(szBuf, sizeof(char));

    assert(_read(ptr, ptrBuf, 0)==-1);
}

void read_test_out_of_buffer()          //размер блока больше размера буфера
{
    _init(1, 15);
    VA ptr="00000000";
    _malloc(&ptr, 5);
    _write(ptr, "first", 5);
    const int szBuf=3;
    char* ptrBuf=calloc(szBuf, sizeof(char));

    assert(_read(ptr, ptrBuf, szBuf)==-2);
}

void read_test_success()          //успешное чтение информации из блока
{
    _init(1, 15);
    VA ptr="00000000";
    _malloc(&ptr, 5);
    _write(ptr, "first", 5);
    const int szBuf=5;
    char* ptrBuf=calloc(szBuf, sizeof(char));

    assert(_read(ptr, ptrBuf, szBuf)==0);
}

void read_test_block_is_empty()          //попытка чтения из пустого блока
{
    _init(1, 15);
    VA ptr="00000000";
    _malloc(&ptr, 5);
    const int szBuf=7;
    char* ptrBuf=calloc(szBuf, sizeof(char));

    assert(_read(ptr, ptrBuf, szBuf)==-1);
}

void custom_test()
{
    printf("\nCustom test...\n");
    _init(1, 10);
    VA ptr="00000000";
    VA ptr1="00000001";
    VA ptr2="00000010";
    VA ptr3="00000011";
    VA ptr4="00000100";

    assert(_malloc(&ptr, 2)==0);            //добавление блока
    assert(_malloc(&ptr1, 2)==0);           //добавление блока
    assert(_malloc(&ptr2, 2)==0);           //добавление блока
    assert(_malloc(&ptr3, 1)==0);           //добавление блока

    assert(_write(ptr, "11", 2)==0);
    assert(_write(ptr1, "22", 2)==0);
    assert(_write(ptr2, "33", 2)==0);
    assert(_write(ptr3, "4", 1)==0);

    printMemory();

    assert(_free(ptr1)==0);                 //удаление блока

    assert(_malloc(&ptr4, 4)==0);           //добавление блока (будет производиться сжатие)

    assert(_write(ptr4, "5555", 4)==0);

    printMemory();

    printf("\nCustom test passed successfully!\n");

}

void run_load_tests()
{
    int max_size = 60000;
    int size;
    for (size=10000; size<=max_size; size+=10000)
        load_test(size);
}

void load_test(int size)
{
    FILE *fp;
    fp = fopen("testCompression.txt", "a");

    struct timeval ta, te;

    int size_block=1;

    fprintf(fp, "\nTesting compression\nSize - %d \n", size);
    _init(1, size);

    int i;

    for (i=0; i<size/size_block; i++)
    {
        VA ptr=convertToVA(i);
        _malloc(&ptr, size_block);
    }

    for (i=0; i<size/size_block; i+=2)
    {
        VA ptr=convertToVA(i);
        _free(ptr);
    }

    gettimeofday(&ta, NULL);

    compressionMemory();

    gettimeofday(&te, NULL);

    fprintf(fp, "Time: %lf msec\n", (te.tv_sec - ta.tv_sec)*1000.0 + (te.tv_usec - ta.tv_usec)/1000.0);

}
