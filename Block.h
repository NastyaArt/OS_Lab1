#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "mmemory.h"

#define ADDRESS_SIZE 8              //������ ������
#define TRUE 1
#define FALSE 0

struct block{
    VA address;                         //����� �����
    int size;                           //������ �����
    int offset;                         //����� �� ������ ������
    char isEmpty;                       //�������� �� ���� ������
	struct block *next;                 //��������� �� ��������� ����
};

struct block *createBlock(VA* address, int size, int offset);  //������� ����� ���� � ��������� ��������, ������� � �������

#endif //MEMORY_BLOCK_H
