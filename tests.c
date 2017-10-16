#include <stdio.h>
#include <assert.h>
#include "tests.h"
#include "manager.h"

void run_init_tests()
{
    printf("\nInit tests...\n");

    init_test_1();
    init_test_2();
    init_test_3();

    printf("\nInit tests passed successfully!\n");
}

void init_test_1()          //некорректные данные
{
    assert(_init(-5)==-1);
}

void init_test_2()          //попытка выделить память больше допустимого
{
    assert(_init(270)==-1);
}

void init_test_3()          //успешная инициализация
{
    assert(_init(180)==0);
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

void malloc_test_1()          //блок больше всей памяти
{
    _init(100);
    VA ptr="00000000";

    assert(_malloc(&ptr, 110)==-2);
}

void malloc_test_2()          //некорректный адрес
{
    _init(100);
    VA ptr="00test70";

    assert(_malloc(&ptr, 10)==-1);
}

void malloc_test_3()          //успешное добавление блока
{
    _init(100);
    VA ptr="00000000";

    assert(_malloc(&ptr, 40)==0);
}

void malloc_test_4()          //нехватка памяти
{
    _init(100);
    VA ptr1="00000000";
    VA ptr2="00000001";
    VA ptr3="00000010";
    _malloc(&ptr1, 40);
    _malloc(&ptr2, 40);

    assert(_malloc(&ptr3, 40)==-2);
}

void malloc_test_5()          //адрес уже занят
{
    _init(100);
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

void free_test_1()          //некорректный адрес
{
    _init(100);
    VA ptr="00000000";
    VA ptr1="00test70";
    _malloc(&ptr, 40);

    assert(_free(ptr1)==-1);
}

void free_test_2()          //успешное удаление блока
{
    _init(100);
    VA ptr="00000000";
    _malloc(&ptr, 40);

    assert(_free(ptr)==0);
}

void free_test_3()          //адрес не указывает ни на один блок
{
    _init(100);
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

void write_test_1()          //некорректный адрес
{
    _init(15);
    VA ptr="00000000";
    VA ptr1="000test70";
    _malloc(&ptr, 6);

    assert(_write(ptr1, "string", 6)==-1);
}

void write_test_2()          //адрес не указывает ни на один блок
{
    _init(15);
    VA ptr="00000000";
    VA ptr1="00000001";
    _malloc(&ptr, 6);

    assert(_write(ptr1, "string", 6)==-1);
}

void write_test_3()          //размер буфера не соответствует буферу
{
    _init(15);
    VA ptr="00000000";
    _malloc(&ptr, 6);

    assert(_write(ptr, "string", 4)==-1);
}

void write_test_4()          //размер буфера больше размера блока
{
    _init(15);
    VA ptr="00000000";
    _malloc(&ptr, 4);

    assert(_write(ptr, "string", 6)==-2);
}

void write_test_5()          //успешная запись информации в блок
{
    _init(15);
    VA ptr="00000000";
    _malloc(&ptr, 5);

    assert(_write(ptr, "first", 5)==0);
}

void write_test_6()          //попытка записи в уже заполненный блок
{
    _init(15);
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

void read_test_1()          //некорректный адрес
{
    _init(15);
    VA ptr="00000000";
    VA ptr1="000test70";
    _malloc(&ptr, 5);
    _write(ptr, "first", 5);
    const int szBuf=5;
    char* ptrBuf=calloc(szBuf, sizeof(char));

    assert(_read(ptr1, ptrBuf, szBuf)==-1);
}

void read_test_2()          //адрес не указывает ни на один блок
{
    _init(15);
    VA ptr="00000000";
    VA ptr1="00000001";
    _malloc(&ptr, 5);
    _write(ptr, "first", 5);
    const int szBuf=5;
    char* ptrBuf=calloc(szBuf, sizeof(char));

    assert(_read(ptr1, ptrBuf, szBuf)==-1);
}

void read_test_3()          //некорректный размер буфера
{
    _init(15);
    VA ptr="00000000";
    _malloc(&ptr, 5);
    _write(ptr, "first", 5);
    const int szBuf=5;
    char* ptrBuf=calloc(szBuf, sizeof(char));

    assert(_read(ptr, ptrBuf, 0)==-1);
}

void read_test_4()          //размер блока больше размера буфера
{
    _init(15);
    VA ptr="00000000";
    _malloc(&ptr, 5);
    _write(ptr, "first", 5);
    const int szBuf=3;
    char* ptrBuf=calloc(szBuf, sizeof(char));

    assert(_read(ptr, ptrBuf, szBuf)==-2);
}

void read_test_5()          //успешное чтение информации из блока
{
    _init(15);
    VA ptr="00000000";
    _malloc(&ptr, 5);
    _write(ptr, "first", 5);
    const int szBuf=5;
    char* ptrBuf=calloc(szBuf, sizeof(char));

    assert(_read(ptr, ptrBuf, szBuf)==0);
}

void read_test_6()          //попытка чтения из пустого блока
{
    _init(15);
    VA ptr="00000000";
    _malloc(&ptr, 5);
    const int szBuf=7;
    char* ptrBuf=calloc(szBuf, sizeof(char));

    assert(_read(ptr, ptrBuf, szBuf)==-1);
}

void custom_test()
{
    printf("\nCustom test...\n");
    _init(10);
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

void load_test()
{
    int size = 255;
    int size_block=1;
    _init(size);

    int i;
    for (i=0; i<size/size_block; i++)
    {
        VA ptr=convertToVA(i);
        _malloc(&ptr, size_block);
        _write(ptr, "i", size_block);
    }
    printMemory();

    for (i=0; i<size/size_block; i+=2)
    {
        VA ptr=convertToVA(i);
        _free(ptr);
    }
    printMemory();
    VA ptr=convertToVA(size+1);

    _malloc(&ptr, 5);

    _write(ptr, "block", 5);
    printMemory();
/*    VA ptr="00000000";
    VA ptr1="00000001";
    VA ptr2="00000010";
    VA ptr3="00000011";
    VA ptr4="00000100";
    VA ptr5="00011100";
    VA ptr6="00000101";
    VA ptr7="00000111";
    VA ptr8="00001000";
    VA ptr9="00001001";
    VA ptr10="00001011";

    assert(_malloc(&ptr, 20)==0);            //добавление блока
    assert(_malloc(&ptr1, 20)==0);           //добавление блока
    assert(_malloc(&ptr2, 20)==0);           //добавление блока
    assert(_malloc(&ptr3, 20)==0);           //добавление блока
    assert(_malloc(&ptr4, 20)==0);            //добавление блока
    assert(_malloc(&ptr5, 20)==0);           //добавление блока
    assert(_malloc(&ptr6, 20)==0);           //добавление блока
    assert(_malloc(&ptr7, 20)==0);           //добавление блока
    assert(_malloc(&ptr8, 20)==0);           //добавление блока
    assert(_malloc(&ptr9, 20)==0);           //добавление блока

    assert(_free(ptr1)==0);                 //удаление блока
    assert(_free(ptr2)==0);                 //удаление блока
    assert(_free(ptr3)==0);                 //удаление блока
    assert(_free(ptr5)==0);                 //удаление блока
    assert(_free(ptr7)==0);                 //удаление блока
    assert(_free(ptr9)==0);                 //удаление блока

    //подсчет времени на сжатие внутри compression memory
    assert(_malloc(&ptr10, 70)==0);           //добавление блока (будет производиться сжатие)
*/

}
