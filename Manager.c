#include "manager.h"

//����� ������ (��� �������)
void printMemory()
{
    int i;
	printf( "\nMemory:\n" );
	for( i=0; i < Manager->size; i++)
		printf("%c", Manager->data[i] );
}

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
    //������, ���� ����� ���� ������ � ������������
    if (Manager->blocks==NULL)
    {
        Manager->blocks=newBlock;
        return TRUE;
    }
    struct block *curBlock = Manager->blocks;
    while (curBlock!=NULL)
    {
        //������, ���� ����� ���� ��������� � ������
        if (newBlock->offset==0)
        {
            Manager->blocks=newBlock;
            newBlock->next=curBlock;
            return TRUE;
        }
        //������, ���� ���� ���������
        if (curBlock->next==NULL)
        {
            curBlock->next=newBlock;
            return TRUE;
        }
        //���� ���� ����� ���������� ����� ����� �������
        if (curBlock->offset < newBlock->offset && curBlock->next->offset > newBlock->offset)
        {
            newBlock->next=curBlock->next;
            curBlock->next=newBlock;
            return TRUE;
        }
        curBlock=curBlock->next;
    }
    return FALSE;
}

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

    int offset, add;
    offset=findPlace(szBlock);                      // ��������, ���� �� �����
    if (offset>=0)
        add=addBlock(*ptr, szBlock, offset);            //������� ���� � offset
    else
        return 1;
    if (add!=TRUE)
        return 1;
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

    //������������ ������, ������� ������ � data (�������� ������)


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
    //����� ����� �� ������
    //���� �����:
    //�������� ��������
    //��������� ������ � ����� pBuffer=data
    if (validVA(ptr)==FALSE || szBuffer<=0)             //�������� �������� �� ����� � ������ ������ �����������
        return -1;
    struct block *curBlock;
    curBlock=findBlockByVA(ptr);                        //����� ����� �� ������
    if (curBlock==NULL)
        return -1;
    if (curBlock->size>szBuffer)                        //�������� ��������
        return -2;
    int i, j;
    char* str=pBuffer;
    printf("\nString - %s", str);
    for (i = curBlock->offset, j=0; i<curBlock->offset+curBlock->size, j<strlen(str); i++, j++)     //���������� ������ � Manager->data �� pBuffer
    {
        str[j]=Manager->data[i];
        printf("\nAdd cifra - %c", str[j]);
    }
   // pBuffer=str;
   // memcpy(pBuffer, str, szBuffer);
    printf("\nBuffer inside - %s", str);
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
    if (validVA(ptr)==FALSE || szBuffer<=0)             //�������� �������� �� ����� � ������ ������ �����������
        return -1;
    struct block *curBlock;
    curBlock=findBlockByVA(ptr);                        //����� ����� �� ������
    if (curBlock==NULL)
        return -1;
    if (curBlock->size<szBuffer || strlen(pBuffer)>curBlock->size)           //�������� ��������
        return -2;
    int i, j;
    char* str=pBuffer;
    printf("\nString - %s", str);
    for (i = curBlock->offset, j=0; i<curBlock->offset+curBlock->size, j<strlen(str); i++, j++)     //���������� ������ � Manager->data �� pBuffer
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
    printMemory();
    return 0;
}
