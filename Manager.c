#include "manager.h"

//вывод памяти (для отладки)
void printMemory()
{
    int i;
	printf( "\nMemory:\n" );
	for( i=0; i < Manager->size; i++)
		printf("%c", Manager->data[i] );
}
/*
//перевод адреса в целое число
int VAToInt (VA ptr)
{
    int dec = 0;
    int i=0, exp=0;
    for (i = strlen(ptr)-1, exp = 0; i >= 0; i--, exp++) {
        int num = ptr[i] - '0';
        dec += num * pow(2, exp);
    }
    printf("\nNumber - %d", dec);
    return dec;
}
*/
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
/*    if (VAToInt(ptr) >= MAX_MEMORY_SIZE) {     //адресов строго как размер менеджера, поэтому превышать размер нельзя
        return FALSE;
    }
    */
    return TRUE;
}

//проверка,является ли адрес свободным
int isFreeVA(VA ptr)
{
    struct block *curBlock = Manager->blocks;          //получаем из менеджера ссылку на первый блок
    while (curBlock!=NULL)                      //перебираем все блоки в поиске нужного адреса
    {
        if (strcmp(curBlock->address, ptr)==0) //если нашли такой адрес - то false
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
    return -1;
}

//добавлениие блока в память
int addBlock(VA address, int size, int offset)
{
    struct block *newBlock;

    newBlock = createBlock(address, size, offset);

    if (Manager->blocks==NULL)                          //случай, если новый блок первый и единственный
    {
        Manager->blocks=newBlock;

        return TRUE;
    }
    struct block *curBlock = Manager->blocks;

    while (curBlock!=NULL)
    {
        if (newBlock->offset==0)                        //случай, если новый блок добавляем в начало
        {
            Manager->blocks=newBlock;
            newBlock->next=curBlock;
            return TRUE;
        }

        if (curBlock->next==NULL)                       //случай, если блок последний
        {
            curBlock->next=newBlock;
            return TRUE;
        }

        if (curBlock->offset+size == newBlock->offset /*&& curBlock->next->offset > newBlock->offset+size*/)  //если блок будет находиться между двумя блоками
        {
            newBlock->next=curBlock->next;
            curBlock->next=newBlock;
            return TRUE;
        }
        curBlock=curBlock->next;
    }
    return FALSE;
}

//удаление блока из списка
int delBlock(struct block * findBlock)
{
	if (Manager->blocks==findBlock)
	{
        Manager->blocks=findBlock->next;
        return TRUE;
	}
    struct block* firstBlock = Manager->blocks;
	while(firstBlock->next != NULL)
	{
	    if (firstBlock->next == findBlock)
	    {
	        firstBlock->next = findBlock->next;
	        return TRUE;
	    }
		firstBlock = firstBlock->next;
	}
    return FALSE;
}

//поиск блока по адресу
struct block *findBlockByVA(VA ptr)
{
    struct block *curBlock = Manager->blocks;           //получаем из менеджера ссылку на первый блок
    while (curBlock!=NULL)                              //перебираем все блоки в поиске нужного блока
    {
        if (strcmp(curBlock->address, ptr)==0)          //если нашли его, то возвращаем
            return curBlock;
        curBlock=curBlock->next;
    }
    return NULL;

}

//сжатие памяти
void compressionMemory()
{
  //  printf("\nCompression Memory...");
    struct block *curBlock = Manager->blocks;          //получаем из менеджера ссылку на первый блок
    int curOffset = 0;

    while (curBlock!=NULL)                              //перебираем все блоки в поиске пустых мест
    {
        if (curBlock->offset>curOffset){                //если между блоками есть пустое место
            moveData(curBlock->offset, curOffset, curBlock->size);

            curBlock->offset=curOffset;
            curOffset+=curBlock->size;

            curBlock=curBlock->next;
        }
        else
        {
            curOffset+=curBlock->size;
            curBlock=curBlock->next;
        }
    }
}

//перемещение данных в памяти
void moveData(int curOffset, int newOffset, int size)
{
    char* str=(char*)malloc(size);

    int i, j;

    for (i = curOffset, j=0; i<curOffset+size && j<size; i++, j++)     //записываем данные во временный массив
    {
        str[j]=Manager->data[i];
        Manager->data[i]='0';
    }

    for (i = newOffset, j=0; i<newOffset+size && j<size; i++, j++)     //записываем данные в Manager->data из временного массива
    {
        Manager->data[i]=str[j];
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
    if (validVA(*ptr)==FALSE)                               //проверка является ли адрес корректным
        return -1;
    if (isFreeVA(*ptr)==FALSE)                              //проверка является ли адрес свободным
        return -1;

    int offset, add;
    offset=findPlace(szBlock);                              // проверка, есть ли место
    if (offset>=0)
        add=addBlock(*ptr, szBlock, offset);                //создаем блок в offset
    else {
        compressionMemory();                                //произвдоим сжатие памяти
        offset=findPlace(szBlock);                          //снова проверка, есть ли место
        if (offset>=0)
            add=addBlock(*ptr, szBlock, offset);            //создаем блок в offset
        else
            return -2;                                       //иначе места нет
    }
    if (add==TRUE)
        return 0;
    else return 1;
}

/**
 	@func	_free
 	@brief	Удаление блока памяти

	@param	[in] ptr		адресс блока

	@return	код ошибки
	@retval	0	успешное выполнение
	@retval	-1	неверные параметры
	@retval	1	неизвестная ошибка
 **/
int _free (VA ptr)
{

    if (validVA(ptr)==FALSE)                           //проверка является ли адрес корректным
        return -1;

    struct block *curBlock;
    curBlock=findBlockByVA(ptr);                        //поиск блока по адресу
    if (curBlock==NULL)
        return -1;
    int del;
    del=delBlock(curBlock);                             //удаление блока из списка
    if (del!=TRUE)
        return 1;
    int i;
    for (i = curBlock->offset; i<curBlock->offset+curBlock->size; i++)     //обнуляем данные в Manager->data
    {
        Manager->data[i]='0';
    }
    free(curBlock);                                     //free сам блок
    return 0;
}

/**
 	@func	_read
 	@brief	Чтение информации из блока памяти

	@param	[in] ptr		адресс блока
	@param	[in] pBuffer	адресс буфера куда копируется инфомация
	@param	[in] szBuffer	размер буфера

	@return	код ошибки
	@retval	0	успешное выполнение
	@retval	-1	неверные параметры
	@retval	-2	доступ за пределы блока
	@retval	1	неизвестная ошибка
 **/
int _read (VA ptr, void* pBuffer, size_t szBuffer)
{
    if (validVA(ptr)==FALSE || szBuffer<=0)             //проверка является ли адрес и размер буфера корректными
        return -1;
    struct block *curBlock;
    curBlock=findBlockByVA(ptr);                        //поиск блока по адресу
    if (curBlock==NULL)
        return -1;
    if (curBlock->isEmpty!='1')
        return 1;
    if (curBlock->size>szBuffer)                        //проверка размеров
        return -2;
    int i, j;
    char* str=(char*)malloc(szBuffer);

    for (i = curBlock->offset, j=0; i<curBlock->offset+curBlock->size && j<szBuffer; i++, j++)     //записываем данные в pBuffer из Manager->data
    {
        str[j]=Manager->data[i];
    }

    memcpy(pBuffer, str, szBuffer);                     //передача данных в буфер

    return 0;
}

/**
 	@func	_write
 	@brief	Запись информации в блок памяти

	@param	[in] ptr		адресс блока
	@param	[in] pBuffer	адресс буфера куда копируется инфомация
	@param	[in] szBuffer	размер буфера

	@return	код ошибки
	@retval	0	успешное выполнение
	@retval	-1	неверные параметры
	@retval	-2	доступ за пределы блока
	@retval	1	неизвестная ошибка
 **/
int _write (VA ptr, void* pBuffer, size_t szBuffer)
{
    if (validVA(ptr)==FALSE || strlen(pBuffer)!=szBuffer)             //проверка является ли адрес и размер буфера корректными
        return -1;
    struct block *curBlock;
    curBlock=findBlockByVA(ptr);                        //поиск блока по адресу
    if (curBlock==NULL)
        return -1;
    if (curBlock->isEmpty==FALSE)                           //если блок уже занят
        return -1;
    if (curBlock->size<szBuffer || strlen(pBuffer)>curBlock->size)           //проверка размеров
        return -2;
    int i, j;
    char* str=pBuffer;
    for (i = curBlock->offset, j=0; i<(curBlock->offset+curBlock->size) && j<strlen(str); i++, j++)     //записываем данные в Manager->data из pBuffer
    {
        Manager->data[i]=str[j];
    }
    curBlock->isEmpty=FALSE;                    //и устанавливаем isEmpty=false
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
    //printMemory();
    return 0;
}
