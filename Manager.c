#include "manager.h"

//����� ������ (��� �������)
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
    //����������� ������
    return ptr;
}
*/

//������� ������ � ����� �����
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

//�������� ������
int validVA(VA ptr)
{
    if (strlen(ptr) != ADDRESS_SIZE)  //���� ������ ������ �� ������������ ������������ ������������
        return FALSE;
    int i;
    for (i = 0; i < ADDRESS_SIZE; i++) {    //���� ���� �� �� 0 � 1
        if (ptr[i] != '0' && ptr[i] != '1')
            return FALSE;
    }
    if (VAToInt(ptr) > Manager->size) {     //������� ������ ��� ������ ���������, ������� ��������� ������ ������
        return FALSE;
    }
    return TRUE;
}

/*
int isFreeVA(memManager *manager, VA ptr)
{

    //�������� �� ��������� ������ �� ������ ����
    //���������� ��� ����� � ������ ������� ������
    //���� �� �����, �� true
    //����� false
    return 0;
}
*/

int isFreeVA(VA ptr)
{
    struct block *curBlock = Manager->blocks;          //�������� �� ��������� ������ �� ������ ����
    while (curBlock!=NULL)                      //���������� ��� ����� � ������ ������� ������
    {
        if (strcmp(curBlock->address, ptr)==0) //���� ����� ����� ����� - �� false
            return FALSE;
        curBlock=curBlock->next;
    }
    return TRUE;                                //���� �� �����, �� true
}

//����� ������� ����� � ������
int findPlace(int size)
{
    struct block *curBlock = Manager->blocks;          //�������� �� ��������� ������ �� ������ ����
    int curOffset = 0;
    if (curBlock==NULL)                         //���� ��� ��� �� ������ �����
        return curOffset;
    while (curBlock!=NULL)                      //���������� ��� ����� � ������ ������� �����
    {
        if ((curBlock->offset-curOffset)>=size)         //����� ����� ����� �������
            return curOffset;
        if (curBlock->next==NULL){                      //����� ����� ����� ��������� ������ � ������ ���� ������
            curOffset=curBlock->offset+curBlock->size;
            if ((Manager->size-curOffset)>=size)
                return curOffset;
            else
                return -1;                              //����� ��� ������
        }
        curOffset=curBlock->offset+curBlock->size;      // ��������� � ���������� �����
        curBlock=curBlock->next;
    }
    return -1;
}

void addBlock(VA address, int size, int offset)
{
    struct block *newBlock;
    newBlock = createBlock(address, size, offset);
    //������, ���� ����� ���� ������ � ������������
    if (Manager->blocks==NULL)
    {
        Manager->blocks=newBlock;
        return;
    }
    struct block *curBlock = Manager->blocks;
    while (curBlock!=NULL)
    {
        //������, ���� ����� ���� ��������� � ������
        if (newBlock->offset==0)
        {
            Manager->blocks=newBlock;
            newBlock->next=curBlock;
            return;
        }
        //������, ���� ���� ���������
        if (curBlock->next==NULL)
        {
            curBlock->next=newBlock;
            return;
        }
        //���� ���� ����� ���������� ����� ����� �������
        if (curBlock->offset < newBlock->offset && curBlock->next->offset > newBlock->offset)
        {
            newBlock->next=curBlock->next;
            curBlock->next=newBlock;
            return;
        }
        curBlock=curBlock->next;
    }
    return;
}

void delBlock(struct block * findBlock)
{
	if (Manager->blocks==findBlock)
	{
        Manager->blocks=findBlock->next;
        return;
	}
    struct block* firstBlock = Manager->blocks;
	while(firstBlock->next != NULL)
	{
	    if (firstBlock->next == findBlock)
	    {
	        firstBlock->next = findBlock->next;
	        return;
	    }
		firstBlock = firstBlock->next;
	}

   //��������� ����� � Manager->data
}

struct block *findBlockByVA(VA ptr)
{
    struct block *curBlock = Manager->blocks;          //�������� �� ��������� ������ �� ������ ����
    while (curBlock!=NULL)                      //���������� ��� ����� � ������ ������� �����
    {
        if (strcmp(curBlock->address, ptr)==0) //���� ����� ���, �� ����������
            return curBlock;
        curBlock=curBlock->next;
    }
    return NULL;

}

/**
 	@func	_malloc
 	@brief	�������� ���� ������ ������������� �������

	@param	[out] ptr		������ �����
	@param	[in]  szBlock	������ �����

	@return	��� ������
	@retval	0	�������� ����������
	@retval	-1	�������� ���������
	@retval	-2	�������� ������
	@retval	1	����������� ������
 **/
int _malloc (VA* ptr, size_t szBlock)
{
    if (szBlock>Manager->size)                              //������� �������� ���� ������ ���� ������
        return -2;
    if (validVA(*ptr)==FALSE || isFreeVA(*ptr)==FALSE )                               //�������� �������� �� ����� ���������
        return -1;

    int offset;
    offset=findPlace(szBlock);                      // ��������, ���� �� �����
    if (offset>=0)
        addBlock(*ptr, szBlock, offset);            //������� ���� � offset
    else return 1;

    //���� ��� - ������
    //���� ����� ��� - ������, ������ �� �������


    return 0;
}

/**
 	@func	_free
 	@brief	�������� ����� ������

	@param	[in] ptr		������ �����

	@return	��� ������
	@retval	0	�������� ����������
	@retval	-1	�������� ���������
	@retval	1	����������� ������
 **/
int _free (VA ptr)
{
    //����� ����� �� ������
    //���� �����:
    //������������ ������, ������� ������ � data (�������� ������)
    //�������� ����� �� ������
    //free ��� ����

    if (validVA(ptr)==FALSE)                           //�������� �������� �� ����� ����������
        return -1;

    struct block *curBlock;
    curBlock=findBlockByVA(ptr);
    if (curBlock==NULL)
        return -1;
    delBlock(curBlock);
    free(curBlock);
    return 0;
}

int _read (VA ptr, void* pBuffer, size_t szBuffer)
{
    //����� ����� �� ������
    //���� �����:
    //�������� ��������
    //��������� ������ � ����� pBuffer=data
    return 0;
}

int _write (VA ptr, void* pBuffer, size_t szBuffer)
{
    //����� ����� �� ������
    //���� �����:
    //�������� ��������
    //���������� ������ � Manager->data �� pBuffer
    //� ������������� isEmpty=false
    return 0;
}

/**
 	@func	_init
 	@brief	������������� ������ ��������� ������

	@param	[in] n		���������� �������
	@param	[in] szPage	������ ��������

	� �������� 1 � 2 ����� ����� ������ ������������� ��� n*szPage

	@return	��� ������
	@retval	0	�������� ����������
	@retval	-1	�������� ���������
	@retval	1	����������� ������
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
