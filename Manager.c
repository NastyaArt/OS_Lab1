#include "manager.h"

void printMemory(memManager *manager)
{
    int i;
	printf( "\nMemory:\n" );
	for( i=0; i < manager->size; i++)
		printf("%c", manager->data[i] );
}
/*
VA intToVA (int dec)
{
    VA ptr;
    //конвертация адреса
    return ptr;
}
*/
int VAToInt (VA ptr)
{
    int dec = 0;
    int i=0, exp=0;
    for (i = strlen(ptr)-1, exp = 0; i >= 0; i--, exp++) {
        int num = ptr[i] - '0';
        dec += num * pow(2, exp);
    }
    return dec;
}

int validVA(VA ptr)
{
    if (strlen(ptr) != ADDRESS_SIZE)  //если размер адреса не соответсвует виртуальному пространству
        return 0;
    int i;
    for (i = 0; i < ADDRESS_SIZE; i++) {    //если сост не из 0 и 1
        if (ptr[i] != '0' && ptr[i] != '1')
            return 0;
    }
    if (VAToInt(ptr) > Manager->size) {     //адресов строго как размер менеджера, поэтому превышать размер нельзя
        return 0;
    }
    return 1;
}

int isFreeVA(memManager *manager, VA ptr)
{
    //получаем из менеджера ссылку на первый блок
    //перебираем все блоки в поиске нужного адреса
    //если не нашли, то true
    //иначе false
    return 0;
}

int findAdress(VA ptr)
{
    block *curBlock = Manager->blocks;
    while (curBlock!=NULL)
    {
        if (strcmp(curBlock->address, ptr)==0)
            return 0;
        curBlock=curBlock->next;
    }
    return 1;
}

int findPlace(memManager *manager, int size)
{
    //ищем пустое место в памяти
    //если нашли - возвращаем offset на него
    return 0;
}

int _malloc (VA* ptr, size_t szBlock)
{

    if (Manager->blocks==NULL){
        Manager->blocks=createBlock(ptr, szBlock, 0);
        return 0;
    }
   //проверка является ли адрес свободным
   // проверка, есть ли место
    //если нет - сжатие
    //если опять нет - ошибка, памяти не хватает
    //если есть - генирация адреса
   // createBlock
   // добавление нового блока в связный список

    return 0;
}

int _free (VA ptr)
{
    //поиск блока по адресу
    //если нашли:
    //освобождение данных, занятых блоком в data (затираем нулями)
    //удаление блока из списка
    //free сам блок
    return 0;

}

int _read (VA ptr, void* pBuffer, size_t szBuffer)
{
    //поиск блока по адресу
    //если нашли:
    //проверка размеров
    //считываем данные в буфер pBuffer=data
    return 0;
}

int _write (VA ptr, void* pBuffer, size_t szBuffer)
{
    //поиск блока по адресу
    //если нашли:
    //проверка размеров
    //записываем данные в Manager->data из pBuffer
    //и устанавливаем isEmpty=false
    return 0;
}

int _init (int sizeMemory)
{
    if (sizeMemory < 1 || sizeMemory > MAX_MEMORY_SIZE)
        return -1;
    Manager = (memManager *)malloc(sizeof(memManager));
    Manager->data=(char *)malloc(sizeMemory*sizeof(char));
    if (Manager == NULL || Manager->data== NULL)
        return 1;
    Manager->size = sizeMemory;
    memset(Manager->data, '0', Manager->size);
    Manager->blocks = NULL;
    printMemory(Manager);
    return 0;
}
