#include "manager.h"

//����� ������ (��� �������)
void printMemory()
{
    int i;
	printf( "\nMemory:\n" );
	for( i=0; i < Manager->size; i++)
		printf("%c", Manager->data[i] );
}
/*
//������� ������ � ����� �����
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
/*    if (VAToInt(ptr) >= MAX_MEMORY_SIZE) {     //������� ������ ��� ������ ���������, ������� ��������� ������ ������
        return FALSE;
    }
    */
    return TRUE;
}

//��������,�������� �� ����� ���������
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

//����������� ����� � ������
int addBlock(VA address, int size, int offset)
{
    struct block *newBlock;

    newBlock = createBlock(address, size, offset);

    if (Manager->blocks==NULL)                          //������, ���� ����� ���� ������ � ������������
    {
        Manager->blocks=newBlock;

        return TRUE;
    }
    struct block *curBlock = Manager->blocks;

    while (curBlock!=NULL)
    {
        if (newBlock->offset==0)                        //������, ���� ����� ���� ��������� � ������
        {
            Manager->blocks=newBlock;
            newBlock->next=curBlock;
            return TRUE;
        }

        if (curBlock->next==NULL)                       //������, ���� ���� ���������
        {
            curBlock->next=newBlock;
            return TRUE;
        }

        if (curBlock->offset+size == newBlock->offset /*&& curBlock->next->offset > newBlock->offset+size*/)  //���� ���� ����� ���������� ����� ����� �������
        {
            newBlock->next=curBlock->next;
            curBlock->next=newBlock;
            return TRUE;
        }
        curBlock=curBlock->next;
    }
    return FALSE;
}

//�������� ����� �� ������
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

//����� ����� �� ������
struct block *findBlockByVA(VA ptr)
{
    struct block *curBlock = Manager->blocks;           //�������� �� ��������� ������ �� ������ ����
    while (curBlock!=NULL)                              //���������� ��� ����� � ������ ������� �����
    {
        if (strcmp(curBlock->address, ptr)==0)          //���� ����� ���, �� ����������
            return curBlock;
        curBlock=curBlock->next;
    }
    return NULL;

}

//������ ������
void compressionMemory()
{
  //  printf("\nCompression Memory...");
    struct block *curBlock = Manager->blocks;          //�������� �� ��������� ������ �� ������ ����
    int curOffset = 0;

    while (curBlock!=NULL)                              //���������� ��� ����� � ������ ������ ����
    {
        if (curBlock->offset>curOffset){                //���� ����� ������� ���� ������ �����
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

//����������� ������ � ������
void moveData(int curOffset, int newOffset, int size)
{
    char* str=(char*)malloc(size);

    int i, j;

    for (i = curOffset, j=0; i<curOffset+size && j<size; i++, j++)     //���������� ������ �� ��������� ������
    {
        str[j]=Manager->data[i];
        Manager->data[i]='0';
    }

    for (i = newOffset, j=0; i<newOffset+size && j<size; i++, j++)     //���������� ������ � Manager->data �� ���������� �������
    {
        Manager->data[i]=str[j];
    }
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
    if (validVA(*ptr)==FALSE)                               //�������� �������� �� ����� ����������
        return -1;
    if (isFreeVA(*ptr)==FALSE)                              //�������� �������� �� ����� ���������
        return -1;

    int offset, add;
    offset=findPlace(szBlock);                              // ��������, ���� �� �����
    if (offset>=0)
        add=addBlock(*ptr, szBlock, offset);                //������� ���� � offset
    else {
        compressionMemory();                                //���������� ������ ������
        offset=findPlace(szBlock);                          //����� ��������, ���� �� �����
        if (offset>=0)
            add=addBlock(*ptr, szBlock, offset);            //������� ���� � offset
        else
            return -2;                                       //����� ����� ���
    }
    if (add==TRUE)
        return 0;
    else return 1;
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

    if (validVA(ptr)==FALSE)                           //�������� �������� �� ����� ����������
        return -1;

    struct block *curBlock;
    curBlock=findBlockByVA(ptr);                        //����� ����� �� ������
    if (curBlock==NULL)
        return -1;
    int del;
    del=delBlock(curBlock);                             //�������� ����� �� ������
    if (del!=TRUE)
        return 1;
    int i;
    for (i = curBlock->offset; i<curBlock->offset+curBlock->size; i++)     //�������� ������ � Manager->data
    {
        Manager->data[i]='0';
    }
    free(curBlock);                                     //free ��� ����
    return 0;
}

/**
 	@func	_read
 	@brief	������ ���������� �� ����� ������

	@param	[in] ptr		������ �����
	@param	[in] pBuffer	������ ������ ���� ���������� ���������
	@param	[in] szBuffer	������ ������

	@return	��� ������
	@retval	0	�������� ����������
	@retval	-1	�������� ���������
	@retval	-2	������ �� ������� �����
	@retval	1	����������� ������
 **/
int _read (VA ptr, void* pBuffer, size_t szBuffer)
{
    if (validVA(ptr)==FALSE || szBuffer<=0)             //�������� �������� �� ����� � ������ ������ �����������
        return -1;
    struct block *curBlock;
    curBlock=findBlockByVA(ptr);                        //����� ����� �� ������
    if (curBlock==NULL)
        return -1;
    if (curBlock->isEmpty!='1')
        return 1;
    if (curBlock->size>szBuffer)                        //�������� ��������
        return -2;
    int i, j;
    char* str=(char*)malloc(szBuffer);

    for (i = curBlock->offset, j=0; i<curBlock->offset+curBlock->size && j<szBuffer; i++, j++)     //���������� ������ � pBuffer �� Manager->data
    {
        str[j]=Manager->data[i];
    }

    memcpy(pBuffer, str, szBuffer);                     //�������� ������ � �����

    return 0;
}

/**
 	@func	_write
 	@brief	������ ���������� � ���� ������

	@param	[in] ptr		������ �����
	@param	[in] pBuffer	������ ������ ���� ���������� ���������
	@param	[in] szBuffer	������ ������

	@return	��� ������
	@retval	0	�������� ����������
	@retval	-1	�������� ���������
	@retval	-2	������ �� ������� �����
	@retval	1	����������� ������
 **/
int _write (VA ptr, void* pBuffer, size_t szBuffer)
{
    if (validVA(ptr)==FALSE || strlen(pBuffer)!=szBuffer)             //�������� �������� �� ����� � ������ ������ �����������
        return -1;
    struct block *curBlock;
    curBlock=findBlockByVA(ptr);                        //����� ����� �� ������
    if (curBlock==NULL)
        return -1;
    if (curBlock->isEmpty==FALSE)                           //���� ���� ��� �����
        return -1;
    if (curBlock->size<szBuffer || strlen(pBuffer)>curBlock->size)           //�������� ��������
        return -2;
    int i, j;
    char* str=pBuffer;
    for (i = curBlock->offset, j=0; i<(curBlock->offset+curBlock->size) && j<strlen(str); i++, j++)     //���������� ������ � Manager->data �� pBuffer
    {
        Manager->data[i]=str[j];
    }
    curBlock->isEmpty=FALSE;                    //� ������������� isEmpty=false
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
    //printMemory();
    return 0;
}
