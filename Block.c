#include "Block.h"

//создает новый блок с указанным размером, адресом и сдвигом
struct block *createBlock(VA address, int size, int offset)
{
    struct block *newBlock;
    newBlock=(struct block *)malloc(sizeof(struct block));
    strcpy(newBlock->address, address);
    newBlock->size=size;
    newBlock->offset=offset;
    newBlock->isEmpty=TRUE;
    newBlock->next=NULL;
    return newBlock;
}
