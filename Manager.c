#include "manager.h"

void printMemory(memManager *manager)
{
    int i;
	printf( "\nMemory:\n" );
	for( i=0; i < manager->size; i++)
		printf("%c", manager->data[i] );
}
/*
VA intToVA (int dec)
{
    VA ptr;
    //����������� ������
    return ptr;
}
*/
int VAToInt (VA ptr)
{
    int dec = 0;
    int i=0, exp=0;
    for (i = strlen(ptr)-1, exp = 0; i >= 0; i--, exp++) {
        int num = ptr[i] - '0';
        dec += num * pow(2, exp);
    }
    return dec;
}

int validVA(VA ptr)
{
    if (strlen(ptr) != ADDRESS_SIZE)  //���� ������ ������ �� ������������ ������������ ������������
        return 0;
    int i;
    for (i = 0; i < ADDRESS_SIZE; i++) {    //���� ���� �� �� 0 � 1
        if (ptr[i] != '0' && ptr[i] != '1')
            return 0;
    }
    if (VAToInt(ptr) > Manager->size) {     //������� ������ ��� ������ ���������, ������� ��������� ������ ������
        return 0;
    }
    return 1;
}

int isFreeVA(memManager *manager, VA ptr)
{
    //�������� �� ��������� ������ �� ������ ����
    //���������� ��� ����� � ������ ������� ������
    //���� �� �����, �� true
    //����� false
    return 0;
}

int findAdress(VA ptr)
{
    block *curBlock = Manager->blocks;
    while (curBlock!=NULL)
    {
        if (strcmp(curBlock->address, ptr)==0)
            return 0;
        curBlock=curBlock->next;
    }
    return 1;
}

int findPlace(memManager *manager, int size)
{
    //���� ������ ����� � ������
    //���� ����� - ���������� offset �� ����
    return 0;
}

int _malloc (VA* ptr, size_t szBlock)
{

    if (Manager->blocks==NULL){
        Manager->blocks=createBlock(ptr, szBlock, 0);
        return 0;
    }
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
