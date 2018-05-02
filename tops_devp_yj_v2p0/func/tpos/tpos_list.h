#ifndef __TPOS_LIST_H__
#define	__TPOS_LIST_H__

#include "tpos_data_type.h"
#include "tpos.h"



//Get offset address of a member in a structure.
//���һ���ṹ�������Ա�ڴ˽ṹ���е�ƫ������
#ifndef offsetof
#define offsetof(type,member) ((unsigned int)&((type*)0)->member)
#endif

//Get structure pointer from it's member
//�ӽṹ�壨type��ĳ��Ա������member��ָ�루ptr��������ýṹ�壨type������ָ�롣
#define container_of(ptr, type, member) ({ \
    const char *__mptr = (char *)(ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})
/*
#define container_of(ptr, type, member) ({ \
    const typeof( ((type *)0)->member ) *__mptr = (ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})
*/



//����ڵ���� �����ھ����Ӧ�ö����У���xList�ṩ����

typedef struct xLIST_ITEM
{
    //void  *item;
    struct xLIST_ITEM *pNext;
}xListItem;


//�������  �ṩ����ǿ��������ķ�ʽ�������Ϊ�����Ķ������

typedef struct xLIST
{
    objMutex  signal;
    unsigned short  uxNumberofItems;
    xListItem *xListHead;
    xListItem *xListEnd;
}xList;


//void  xList_Pool_Init(xList *list,xListItem *listItem_Pool, void *pool, INT16U sizeofitem,INT16U countofitem);
void xList_Init(xList *list);
void xList_Append(xList *list,xListItem *newItem);
void xList_Insert(xList *list,xListItem *newItem);
xListItem * xList_GetItem(xList *list);


#endif	/* __TPOS_LIST_H__ */

