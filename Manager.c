#include "manager.h"

//Вывод памяти (для отладки)
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
//перевод адреса в целое число
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
//проверка адреса
int validVA(VA ptr)
{
    if (strlen(ptr) != ADDRESS_SIZE)  //если размер адреса не соответсвует виртуальному пространству
        return FALSE;
    int i;
    for (i = 0; i < ADDRESS_SIZE; i++) {    //если сост не из 0 и 1
        if (ptr[i] != '0' && ptr[i] != '1')
            return FALSE;
    }
    if (VAToInt(ptr) > Manager->size) {     //адресов строго как размер менеджера, поэтому превышать размер нельзя
        return FALSE;
    }
    return TRUE;
}
/*
int isFreeVA(memManager *manager, VA ptr)
{

    //получаем из менеджера ссылку на первый блок
    //перебираем все блоки в поиске нужного адреса
    //если не нашли, то true
    //иначе false
    return 0;
}
*/
int isFreeVA(VA ptr)
{
    struct block *curBlock = Manager->blocks;          //получаем из менеджера ссылку на первый блок
    while (curBlock!=NULL)                      //перебираем все блоки в поиске нужного адреса
    {
        if (strcmp(curBlock->address, ptr)==0)  //если нашли адрес - то false
            return FALSE;
        curBlock=curBlock->next;
    }
    return TRUE;                                //если не нашли, то true
}

//поиск пустого места в памяти
int findPlace(int size)
{
    struct block *curBlock = Manager->blocks;          //получаем из менеджера ссылку на первый блок
    int curOffset = 0;
    if (curBlock==NULL)                         //если еще нет ни одного блока
        return curOffset;
    while (curBlock!=NULL)                      //перебираем все блоки в поиске пустого места
    {
        if ((curBlock->offset-curOffset)>=size)         //поиск места между блоками
            return curOffset;
        if (curBlock->next==NULL){                      //поиск места между последним блоком и концом всей памяти
            curOffset=curBlock->offset+curBlock->size;
            if ((Manager->size-curOffset)>=size)
                return curOffset;
            else
                return -1;                              //места нет совсем
        }
        curOffset=curBlock->offset+curBlock->size;      // переходим к следующему блоку
        curBlock=curBlock->next;
    }
}

void addBlock(VA* address, int size, int offset)
{
    struct block *newBlock;
    newBlock = createBlock(address, size, offset);
    //случай, если новый блок первый и единственный
    if (Manager->blocks==NULL)
    {
        Manager->blocks=newBlock;
        return;
    }
    struct block *curBlock = Manager->blocks;
    while (curBlock!=NULL)
    {
        //случай, если новый блок добавляем в начало
        if (newBlock->offset==0)
        {
            Manager->blocks=newBlock;
            newBlock->next=curBlock;
            return;
        }
        //случай, если блок последний
        if (curBlock->next==NULL)
        {
            curBlock->next=newBlock;
            return;
        }
        //если блок будет находиться между двумя блоками
        if (curBlock->offset < newBlock->offset && curBlock->next->offset > newBlock->offset)
        {
            newBlock->next=curBlock->next;
            curBlock->next=newBlock;
            return;
        }
        curBlock=curBlock->next;
    }

}

/**
 	@func	_malloc
 	@brief	Выделяет блок памяти определенного размера

	@param	[out] ptr		адресс блока
	@param	[in]  szBlock	размер блока

	@return	код ошибки
	@retval	0	успешное выполнение
	@retval	-1	неверные параметры
	@retval	-2	нехватка памяти
	@retval	1	неизвестная ошибка
 **/
int _malloc (VA* ptr, size_t szBlock)
{
    if (szBlock>Manager->size)                              //попытка выделить блок больше всей памяти
        return -2;
    if (isFreeVA(ptr)==FALSE)                               //проверка является ли адрес свободным
        return -1;

    int offset;
    offset=findPlace(szBlock);
    if (offset>=0)

    addBlock(ptr, szBlock, offset);            //создаем блок в offset
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

/**
 	@func	_init
 	@brief	Инициализация модели менеджера памяти

	@param	[in] n		количество страниц
	@param	[in] szPage	размер страницы

	В варианте 1 и 2 общий объем памяти расчитывается как n*szPage

	@return	код ошибки
	@retval	0	успешное выполнение
	@retval	-1	неверные параметры
	@retval	1	неизвестная ошибка
 **/
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
