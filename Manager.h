#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mem.h>
#include <math.h>
#include "block.h"
#include "mmemory.h"

#define MAX_MEMORY_SIZE 256            //максимальный размер участка памяти
#define TRUE 1
#define FALSE 0

typedef struct{
    int size;
    char* data;
    struct block *blocks;
} memManager;

memManager *Manager;

void printMemory();
//VA intToVA (int dec);
int VAToInt (VA ptr);
int validVA(VA ptr);
int isFreeVA(VA ptr);
void addBlock(VA address, int size, int offset);
void delBlock(struct block *findBlock);
struct block *findBlockByVA(VA ptr);
int findPlace(int size);

#endif //MEMORY_MANAGER_H
