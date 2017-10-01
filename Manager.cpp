#include "manager.h"

VA intToVA (int dec)
{
    VA ptr;
    //конвертация адреса
    return ptr;
}

bool verifVA(VA ptr)
{
    //если размер не 8, то false
    //если состоит из 0 и 1 - то true
    //иначе false
}

bool isFreeVA(MemManager manager, VA ptr)
{
    //получаем из менеджера ссылку на первый блок
    //перебираем все блоки в поиске нужного адреса
    //если не нашли, то true
    //иначе false
}

int findPlace(MemManager manager, int size)
{
    //ищем пустое место в памяти
    //если нашли - возвращаем offset на него
}

int _malloc (VA* ptr, size_t szBlock)
{
    /*
    проверка является ли адрес свободным
    проверка, есть ли место
    если нет - сжатие
    если опять нет - ошибка, памяти не хватает
    если есть - генирация адреса
    createBlock
    добавление нового блока в связный список
    */
}

int _free (VA ptr)
{
    //поиск блока по адресу
    //если нашли:
    //освобождение данных, занятых блоком в data (затираем нулями)
    //удаление блока из списка
    //free сам блок

}

int _read (VA ptr, void* pBuffer, size_t szBuffer)
{
    //поиск блока по адресу
    //если нашли:
    //проверка размеров
    //считываем данные в буфер pBuffer=data
}

int _write (VA ptr, void* pBuffer, size_t szBuffer)
{
    //поиск блока по адресу
    //если нашли:
    //проверка размеров
    //записываем данные в Manager->data из pBuffer
    //и устанавливаем isEmpty=false
}

int _init (int sizeMemory)
{
    if (sizeMemory < 1 || sizeMemory > MAX_MEMORY_SIZE)
        return -1;
    Manager = (struct MemManager *)malloc(sizeof(struct MemManager));
    if (Manager == NULL)
        return 1;
    Manager->size = sizeMemory;
    memset(Manager.data, '0', sizeMemory);
    Manager->blocks = NULL;
    return 0;

}
