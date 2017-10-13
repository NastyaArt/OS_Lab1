#include <stdio.h>
#include <assert.h>
#include "tests.h"
#include "manager.h"

void init_test()
{
    printf("\nInit tests...\n");

    assert(_init(-5)==-1);              //������������ ������
    assert(_init(0)==-1);               //������������ ������
    assert(_init(270)==-1);             //������� �������� ������ ������ �����������
    assert(_init(180)==0);              //�������������
    assert(_init(256)==0);              //�������������

    printf("\nInit tests passed successfully!\n");
}

void malloc_test()
{
    _init(100);
    VA ptr="00000000";
    VA ptr1="00test00";
    VA ptr2="000017011";
    VA ptr3="00000001";
    VA ptr4="00000010";
    VA ptr5="10000011";
    VA ptr6="00000010";

    printf("\nMalloc tests...\n");

    assert(_malloc(&ptr, 110)==-2);      //���� ������ ���� ������
    assert(_malloc(&ptr1, 10)==-1);      //������������ �����
    assert(_malloc(&ptr2, 10)==-1);      //������������ �����
    assert(_malloc(&ptr3, 40)==0);       //���������� �����
    assert(_malloc(&ptr4, 50)==0);       //���������� �����
    assert(_malloc(&ptr5, 20)==-2);      //�������� ������
    assert(_malloc(&ptr6, 10)==-1);      //����� ��� �����

    printf("\nMalloc tests passed successfully!\n");

}

void free_test()
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

    assert(_free(ptr)==-1);       //������������ �����
    assert(_free(ptr1)==-1);      //������������ �����
    assert(_free(ptr2)==0);       //�������� �����
    assert(_free(ptr3)==0);       //�������� �����
    assert(_free(ptr4)==-1);      //������ ����� ���

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

    assert(_write(ptr, "string", 6)==-1);        //�������������� �����
    assert(_write(ptr1, "string", 6)==-1);       //������������ �����
    assert(_write(ptr2, "string", 4)==-1);       //������ ������ �� ������������� ������
    assert(_write(ptr2, "string", 6)==-2);       //������ ������ ������ ������� �����
    assert(_write(ptr2, "first", 5)==0);         //������ ���������� � ����
    assert(_write(ptr3, "scnd", 4)==0);          //������ ���������� � ����
    assert(_write(ptr4, "trd", 3)==0);           //������ ���������� � ����
    assert(_write(ptr5, "newst", 5)==-1);        //������� ������ � ��� ����������� ����

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

    assert(_read(ptr, ptrBuf1, szBuf1)==-1);          //�������������� �����
    assert(_read(ptr1, ptrBuf1, szBuf1)==-1);         //������������ �����
    assert(_read(ptr1, ptrBuf1, -2)==-1);             //������������ ������ ������
    assert(_read(ptr2, ptrBuf2, szBuf2)==-2);         //������ ����� ������ ������� ������
    assert(_read(ptr2, ptrBuf1, szBuf1)==0);          //������ ���������� �� �����
    assert(_read(ptr3, ptrBuf2, szBuf2)==0);          //������ ���������� �� �����
    assert(_read(ptr4, ptrBuf3, szBuf3)==0);          //������ ���������� �� �����

    printf("\nRead tests passed successfully!\n");

}

void custom_test()
{

}
