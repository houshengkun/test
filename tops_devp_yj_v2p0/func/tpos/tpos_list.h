#ifndef __TPOS_LIST_H__
#define	__TPOS_LIST_H__

#include "tpos_data_type.h"
#include "tpos.h"



//Get offset address of a member in a structure.
//获得一个结构体变量成员在此结构体中的偏移量。
#ifndef offsetof
#define offsetof(type,member) ((unsigned int)&((type*)0)->member)
#endif

//Get structure pointer from it's member
//从结构体（type）某成员变量（member）指针（ptr）来求出该结构体（type）的首指针。
#define container_of(ptr, type, member) ({ \
    const char *__mptr = (char *)(ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})
/*
#define container_of(ptr, type, member) ({ \
    const typeof( ((type *)0)->member ) *__mptr = (ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})
*/



//链表节点对象： 附属在具体的应用对象中，由xList提供管理。

typedef struct xLIST_ITEM
{
    //void  *item;
    struct xLIST_ITEM *pNext;
}xListItem;


//链表对象：  提供以增强单向链表的方式管理对象，为操作的顶层对象

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

