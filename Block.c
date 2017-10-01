#include "Block.h"

block *createBlock(VA address, int size, int offset)
{
    block newBlock;
  //  newBlock->address=address;
 //   memcpy (newBlock.address, address, ADDRESS_CAPACITY); -??????????????
    newBlock.size=size;
    newBlock.offset=offset;
    newBlock.isEmpty=1;
}
