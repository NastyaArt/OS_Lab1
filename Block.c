#include "Block.h"

struct block *createBlock(VA address, int size, int offset)
{
    struct block *newBlock;
    newBlock=(struct block *)malloc(sizeof(struct block));
   // newBlock->address=(char *)calloc(strlen(address),sizeof(char));
    strcpy(newBlock->address, address);
    newBlock->size=size;
    newBlock->offset=offset;
    newBlock->isEmpty=TRUE;
    newBlock->next=NULL;
    return newBlock;
}
