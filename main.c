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

    write=_write(ptr1, "1234567891", 10);
    if (write==0){
        printf("\nSuccessful writing");
        printMemory();
    }
    else
        printf("\nError writing - %d", write);

    const int sizeBuf=10;
    //char* ptrBuf = (char*) malloc( sizeof(char) * sizeBuf);
    char ptrBuf[sizeBuf];
    printf("\nBuffer - %s", ptrBuf);
    strcpy(ptrBuf, "0000000000");
    //memset(ptrBuf, '0', sizeBuf);
    printf("\nBuffer - %s", ptrBuf);
    //char *ptrBuf = (char*)calloc(sizeBuf, sizeof(char));
   /* char *ptrBuf=(char *)malloc(sizeBuf*sizeof(char));//"0000000000";// = (char*)calloc(sizeBuf, sizeof(char));
    memset(ptrBuf, "0", sizeBuf);
   */
    read=_read(ptr1, ptrBuf, sizeBuf);
    if (read==0)
        printf("\nSuccessful reading");
    else
        printf("\nError reading - %d", read);
    printf("\nBuffer - %s", ptrBuf);
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
