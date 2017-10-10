#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manager.h"

int main()
{
    int add, free, write, read;
    _init(60);
    VA ptr="00000001";
    VA ptr1="00000010";
    VA ptr2="00000011";

    add =_malloc(&ptr, 5);
    if (add==0)
        printf("\nSuccessful additing");
    else
        printf("\nError adding - %d", add);
    add =_malloc(&ptr1, 10);
    if (add==0)
        printf("\nSuccessful additing");
    else
        printf("\nError adding - %d", add);

    add =_malloc(&ptr2, 5);
    if (add==0)
        printf("\nSuccessful additing");
    else
        printf("\nError adding - %d", add);


    write=_write(ptr, "11111", 5);
    if (write==0){
        printf("\nSuccessful writing");
        printMemory();
    }
    else
        printf("\nError writing - %d", write);

    write=_write(ptr2, "33333", 5);
    if (write==0){
        printf("\nSuccessful writing");
        printMemory();
    }
    else
        printf("\nError writing - %d", write);

    free=_free(ptr1);
    if (free==0)
        printf("\nSuccessful delete");
    else
        printf("\nError delete - %d", free);


    compressionMemory();
    printMemory();
/*////////////// ”даление блока рабочее  ///////////////////
    free=_free(ptr1);
    if (free==0){
        printf("\nSuccessful delete");
        printMemory();
    }
    else
        printf("\nError delete - %d", free);
*/

/*////////////// —читывание рабочее  ///////////////////
    const int sizeBuf=10;
    char* ptrBuf=(char*)malloc(sizeBuf);

    memset(ptrBuf, '0', sizeBuf);

    printf("\nBuffer - %s", ptrBuf);

    read=_read(ptr1, ptrBuf, sizeBuf);
    if (read==0)
        printf("\nSuccessful reading");
    else
        printf("\nError reading - %d", read);
    printf("\nBuffer - %s", ptrBuf);
*/

  /*  add =_malloc(&ptr2, 30);
    if (add==0)
        printf("\nSuccessful additing");
    else
        printf("\nError adding - %d", add);
    free=_free(ptr);
    if (free==0)
        printf("\nSuccessful delete");
    else
        printf("\nError delete - %d", free);

    add =_malloc(&ptr, 10);
    if (add==0)
        printf("\nSuccessful additing");
    else
        printf("\nError adding - %d", add);
*/
    return 0;
}
