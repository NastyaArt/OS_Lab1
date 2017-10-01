#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define ADDRESS_CAPACITY 8              //размер адреса

typedef char* VA;

struct Block{
    VA address;                         //адрес блока
    int size;                           //размер блока
    int offset;                         //сдвиг от начала памяти
    bool isEmpty;                       //является ли блок пустым
	struct Block* next;                 //указатель на следующий блок
};

Block * createBlock(VA address, int size, int offset);  //создает новый блок с указанным размером, адресом и сдвигом
