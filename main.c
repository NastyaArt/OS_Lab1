#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manager.h"

int main()
{
    int add, free;
    _init(60);
    VA ptr="00000001";
    VA ptr1="00000010";
    VA ptr2="00000011";

    add =_malloc(&ptr, 10);
    if (add==0)
        printf("\nSuccessful additing");
    else
        printf("\nError adding - %d", add);
    add =_malloc(&ptr1, 20);
    if (add==0)
        printf("\nSuccessful additing");
    else
        printf("\nError adding - %d", add);
    add =_malloc(&ptr2, 30);
    if (add==0)
        printf("\nSuccessful additing");
    else
        printf("\nError adding - %d", add);
    free=_free(ptr);
    if (free==0)
        printf("\nSuccessful delete");
    else
        printf("\nError delete - %d", free);
/*
    add =_malloc(&ptr, 10);
    if (add==0)
        printf("\nSuccessful additing");
    else
        printf("\nError adding - %d", add);
*/
    return 0;
}
