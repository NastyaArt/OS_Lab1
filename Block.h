#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "mmemory.h"

#define ADDRESS_CAPACITY 8              //размер адреса

typedef struct {
    VA address;                         //адрес блока
    int size;                           //размер блока
    int offset;                         //сдвиг от начала памяти
    char isEmpty;                       //является ли блок пустым
	struct Block* next;                 //указатель на следующий блок
} block;

block *createBlock(VA address, int size, int offset);  //создает новый блок с указанным размером, адресом и сдвигом

#endif //MEMORY_BLOCK_H
