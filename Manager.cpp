#include "manager.h"

VA intToVA (int dec)
{
    VA ptr;
    //����������� ������
    return ptr;
}

bool verifVA(VA ptr)
{
    //���� ������ �� 8, �� false
    //���� ������� �� 0 � 1 - �� true
    //����� false
}

bool isFreeVA(MemManager manager, VA ptr)
{
    //�������� �� ��������� ������ �� ������ ����
    //���������� ��� ����� � ������ ������� ������
    //���� �� �����, �� true
    //����� false
}

int findPlace(MemManager manager, int size)
{
    //���� ������ ����� � ������
    //���� ����� - ���������� offset �� ����
}

int _malloc (VA* ptr, size_t szBlock)
{
    /*
    �������� �������� �� ����� ���������
    ��������, ���� �� �����
    ���� ��� - ������
    ���� ����� ��� - ������, ������ �� �������
    ���� ���� - ��������� ������
    createBlock
    ���������� ������ ����� � ������� ������
    */
}

int _free (VA ptr)
{
    //����� ����� �� ������
    //���� �����:
    //������������ ������, ������� ������ � data (�������� ������)
    //�������� ����� �� ������
    //free ��� ����

}

int _read (VA ptr, void* pBuffer, size_t szBuffer)
{
    //����� ����� �� ������
    //���� �����:
    //�������� ��������
    //��������� ������ � ����� pBuffer=data
}

int _write (VA ptr, void* pBuffer, size_t szBuffer)
{
    //����� ����� �� ������
    //���� �����:
    //�������� ��������
    //���������� ������ � Manager->data �� pBuffer
    //� ������������� isEmpty=false
}

int _init (int sizeMemory)
{
    if (sizeMemory < 1 || sizeMemory > MAX_MEMORY_SIZE)
        return -1;
    Manager = (struct MemManager *)malloc(sizeof(struct MemManager));
    if (Manager == NULL)
        return 1;
    Manager->size = sizeMemory;
    memset(Manager.data, '0', sizeMemory);
    Manager->blocks = NULL;
    return 0;

}
