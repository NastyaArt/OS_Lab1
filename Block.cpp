#include "Block.h"

Block * createBlock(VA address, int size, int offset)
{
    Block newBlock;
  //  newBlock->address=address;
 //   memcpy (newBlock.address, address, ADDRESS_CAPACITY); -??????????????
    newBlock.size=size;
    newBlock.offset=offset;
    newBlock.isEmpty=1;
}
