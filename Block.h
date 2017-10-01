#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define ADDRESS_CAPACITY 8              //������ ������

typedef char* VA;

struct Block{
    VA address;                         //����� �����
    int size;                           //������ �����
    int offset;                         //����� �� ������ ������
    bool isEmpty;                       //�������� �� ���� ������
	struct Block* next;                 //��������� �� ��������� ����
};

Block * createBlock(VA address, int size, int offset);  //������� ����� ���� � ��������� ��������, ������� � �������
