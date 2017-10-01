#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manager.h"

int main()
{
    int v, add, findAdr;
    _init(20);
    VA ptr="00000010";
    v=validVA(ptr);
    add=_malloc(&ptr, 10);
    findAdr=findAdress(ptr);
    printf("\n%d - valid adress, %d - add, %d - findAdr", v, add, findAdr);


    return 0;
}
