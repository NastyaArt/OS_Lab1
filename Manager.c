#include "manager.h"

void printMemory(memManager *manager)
{
    int i;
	printf( "\nMemory:\n" );
	for( i=0; i < manager->size; i++)
		printf("%c", manager->data[i] );
}

VA intToVA (int dec)
{
    VA ptr;
    //����������� ������
    return ptr;
}
int verifVA(VA ptr)
{
    //���� ������ �� 8, �� false
    //���� ������� �� 0 � 1 - �� true
    //����� false
    return 0;
}

int isFreeVA(memManager *manager, VA ptr)
{
    //�������� �� ��������� ������ �� ������ ����
    //���������� ��� ����� � ������ ������� ������
    //���� �� �����, �� true
    //����� false
    return 0;
}

int findPlace(memManager *manager, int size)
{
    //���� ������ ����� � ������
    //���� ����� - ���������� offset �� ����
    return 0;
}

int _malloc (VA* ptr, size_t szBlock)
{

   //�������� �������� �� ����� ���������
   // ��������, ���� �� �����
    //���� ��� - ������
    //���� ����� ��� - ������, ������ �� �������
    //���� ���� - ��������� ������
   // createBlock
   // ���������� ������ ����� � ������� ������

    return 0;
}

int _free (VA ptr)
{
    //����� ����� �� ������
    //���� �����:
    //������������ ������, ������� ������ � data (�������� ������)
    //�������� ����� �� ������
    //free ��� ����
    return 0;

}

int _read (VA ptr, void* pBuffer, size_t szBuffer)
{
    //����� ����� �� ������
    //���� �����:
    //�������� ��������
    //��������� ������ � ����� pBuffer=data
    return 0;
}

int _write (VA ptr, void* pBuffer, size_t szBuffer)
{
    //����� ����� �� ������
    //���� �����:
    //�������� ��������
    //���������� ������ � Manager->data �� pBuffer
    //� ������������� isEmpty=false
    return 0;
}

int _init (int sizeMemory)
{
    if (sizeMemory < 1 || sizeMemory > MAX_MEMORY_SIZE)
        return -1;
    Manager = (memManager *)malloc(sizeof(memManager));
    Manager->data=(char *)malloc(sizeMemory*sizeof(char));
    if (Manager == NULL || Manager->data== NULL)
        return 1;
    Manager->size = sizeMemory;
    memset(Manager->data, '0', Manager->size);
    Manager->blocks = NULL;
    printMemory(Manager);
    return 0;
}
