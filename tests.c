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
    _malloc(&ptr1, 40)
    _malloc(&ptr2, 40)

    assert(_malloc(&ptr, 40)==-2);
}

void malloc_test_5()          //адрес уже занят
{
    _init(100);
    VA ptr1="00000000";
    VA ptr2="00000000";
    _malloc(&ptr1, 40)

    assert(_malloc(&ptr2, 60)==-2);
}

void run_free_tests()
{
    _init(100);

    VA ptr="00test00";
    VA ptr1="000017011";
    VA ptr2="00000001";
    VA ptr3="00000010";
    VA ptr4="00000001";

    _malloc(&ptr2, 30);
    _malloc(&ptr3, 20);

    printf("\nFree tests...\n");

    assert(_free(ptr)==-1);       //некорректный адрес
    assert(_free(ptr1)==-1);      //некорректный адрес
    assert(_free(ptr2)==0);       //удаление блока
    assert(_free(ptr3)==0);       //удаление блока
    assert(_free(ptr4)==-1);      //такого блока нет

    printf("\nFree tests passed successfully!\n");

}

void write_test()
{
    _init(15);

    VA ptr="00000000";
    VA ptr1="000017011";
    VA ptr2="00000001";
    VA ptr3="00000010";
    VA ptr4="00000011";
    VA ptr5="00000001";

    _malloc(&ptr2, 5);
    _malloc(&ptr3, 4);
    _malloc(&ptr4, 3);

    printf("\nWrite tests...\n");

    assert(_write(ptr, "string", 6)==-1);        //несуществующий адрес
    assert(_write(ptr1, "string", 6)==-1);       //некорректный адрес
    assert(_write(ptr2, "string", 4)==-1);       //размер буфера не соответствует буферу
    assert(_write(ptr2, "string", 6)==-2);       //размер буфера больше размера блока
    assert(_write(ptr2, "first", 5)==0);         //запись информации в блок
    assert(_write(ptr3, "scnd", 4)==0);          //запись информации в блок
    assert(_write(ptr4, "trd", 3)==0);           //запись информации в блок
    assert(_write(ptr5, "newst", 5)==-1);        //попытка записи в уже заполненный блок

    printf("\nWrite tests passed successfully!\n");
}

void read_test()
{
    _init(15);

    VA ptr="00000000";
    VA ptr1="000017011";
    VA ptr2="00000001";
    VA ptr3="00000010";
    VA ptr4="00000011";

    _malloc(&ptr2, 5);
    _malloc(&ptr3, 4);
    _malloc(&ptr4, 3);
    _write(ptr2, "first", 5);
    _write(ptr3, "scnd", 4);
    _write(ptr4, "trd", 3);

    const int szBuf1=5;
    char* ptrBuf1=calloc(szBuf1, sizeof(char));

    const int szBuf2=4;
    char* ptrBuf2=calloc(szBuf2, sizeof(char));

    const int szBuf3=3;
    char* ptrBuf3=calloc(szBuf3, sizeof(char));

    printf("\nRead tests...\n");

    assert(_read(ptr, ptrBuf1, szBuf1)==-1);          //несуществующий адрес
    assert(_read(ptr1, ptrBuf1, szBuf1)==-1);         //некорректный адрес
    assert(_read(ptr1, ptrBuf1, -2)==-1);             //некорректный размер адреса
    assert(_read(ptr2, ptrBuf2, szBuf2)==-2);         //размер блока больше размера буфера
    assert(_read(ptr2, ptrBuf1, szBuf1)==0);          //чтение информации из блока
    assert(_read(ptr3, ptrBuf2, szBuf2)==0);          //чтение информации из блока
    assert(_read(ptr4, ptrBuf3, szBuf3)==0);          //чтение информации из блока

    printf("\nRead tests passed successfully!\n");

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
    _init(200);
    VA ptr="00000000";
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

}
