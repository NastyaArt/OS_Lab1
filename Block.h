#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "mmemory.h"

#define ADDRESS_SIZE 8              //размер адреса
#define TRUE 1
#define FALSE 0

struct block{
    VA address[ADDRESS_SIZE];           //адрес блока
    int size;                           //размер блока
    int offset;                         //сдвиг от начала памяти
    char isEmpty;                       //является ли блок пустым
	struct block *next;                 //указатель на следующий блок
};

struct block *createBlock(VA address, int size, int offset);

#endif //MEMORY_BLOCK_H
