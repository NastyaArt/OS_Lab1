#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "mmemory.h"

#define ADDRESS_CAPACITY 8              //������ ������

typedef struct {
    VA address;                         //����� �����
    int size;                           //������ �����
    int offset;                         //����� �� ������ ������
    char isEmpty;                       //�������� �� ���� ������
	struct Block* next;                 //��������� �� ��������� ����
} block;

block *createBlock(VA address, int size, int offset);  //������� ����� ���� � ��������� ��������, ������� � �������

#endif //MEMORY_BLOCK_H
