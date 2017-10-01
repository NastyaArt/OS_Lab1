#pragma once
#include "block.h"
#include "mmemory.h"
#include <malloc.h>
#include <mem.h>
#include <math.h>

#define MAX_MEMORY_SIZE 256            //максимальный размер участка памяти

typedef struct {
    int size;
    char * data;
    Block * blocks;
} MemManager;

MemManager Manager;

VA intToVA (int dec);
bool verifVA(VA ptr);
bool isFreeVA(MemManager manager, VA ptr);
int findPlace(MemManager manager, int size);
