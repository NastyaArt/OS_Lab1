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
    if (v==1)
        printf("\nGood address");
    else
        printf("\nBed address");

    findAdr=isFreeVA(ptr);
    if (findAdr==0)
        printf("\nNo free address");
    else
        printf("\nAddress is free");

    add=_malloc(&ptr, 10);
    if (add==0)
        printf("\nSuccessful additing");
    else
        printf("\nError adding");

    findAdr=isFreeVA(ptr);
    if (findAdr==0)
        printf("\nNo free address");
    else
        printf("\nAddress is free");



    return 0;
}
