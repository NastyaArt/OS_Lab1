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

typedef struct{
    int size;
   // char data[MAX_MEMORY_SIZE];
   char* data;
    block *blocks;
} memManager;

memManager *Manager;

void printMemory();
VA intToVA (int dec);
int verifVA(VA ptr);
int isFreeVA(memManager *manager, VA ptr);
int findPlace(memManager *manager, int size);

#endif //MEMORY_MANAGER_H
