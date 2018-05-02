#include "tpos_list.h"

/*+++
  ���ܣ������ʼ��
---*/
void xList_Init(xList *list)
{
    list->xListHead = NULL;
    list->xListEnd = NULL;
    list->uxNumberofItems = 0;
}

/*+++
  ���ܣ� ��ĩβ���һ������
---*/
void xList_Append(xList *list,xListItem *newItem)
{
    newItem->pNext = NULL;

    tpos_enterCriticalSection();
    if(list->xListEnd == NULL)
    {
        list->xListEnd = newItem;
        list->xListHead = newItem;
        list->uxNumberofItems = 1;
    }
    else
    {
        list->xListEnd->pNext = newItem;
        list->xListEnd  = newItem;
        list->uxNumberofItems  ++;
    }
    tpos_leaveCriticalSection();
}

/*+++
  ���ܣ� ���ײ����һ������
---*/
void xList_Insert(xList *list,xListItem *newItem)
{
    newItem->pNext = list->xListHead;

    tpos_enterCriticalSection();
    if(list->xListHead == NULL)
    {
        list->xListHead = newItem;
        list->xListEnd = newItem;
        list->uxNumberofItems = 1;
    }
    else
    {
        list->xListHead = newItem;
        list->uxNumberofItems  ++;                       
    }
    tpos_leaveCriticalSection();
}

/*+++
  ���ܣ� ��ȡһ������
---*/
xListItem * xList_GetItem( xList *list)
{
    xListItem *item;

    item = NULL;
    tpos_enterCriticalSection();
    if(list->xListHead)
    {
        item = list->xListHead;
        list->xListHead = item->pNext;
        list->uxNumberofItems --;
        if(list->xListHead == NULL)
        {
            list->xListEnd = NULL;
            list->uxNumberofItems = 0;
        }

    }
    tpos_leaveCriticalSection();
    return item;
}

