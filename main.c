#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manager.h"

int main()
{
    int a, z;
    _init(20);
    VA ptr="00000010";
    z=validVA(ptr);
    a=VAToInt(ptr);
    printf("\n%%d - valid adress", a, z);

    return 0;
}
