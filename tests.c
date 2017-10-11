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
    VA ptr4="00000010";

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


}

void read_test()
{

}

void custom_test()
{

}
