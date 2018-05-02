#ifndef __TOPSCOMM_DEVP_TOPS_MEM_H__
#define __TOPSCOMM_DEVP_TOPS_MEM_H__

#include "tpos_data_type.h"

//Get offset address of a member in a structure.
//计算结构体成员变量在结构体中的地址偏移量
#ifndef offsetof
#define offsetof(type,member) ((unsigned int)&((type*)0)->member)
#endif

//Get structure pointer from it's member
//从结构体成员变量地址提取结构体地址
#define container_of(ptr, type, member) ({ \
    const char *__mptr = (char *)(ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})
/*
#define container_of(ptr, type, member) ({ \
    const typeof( ((type *)0)->member ) *__mptr = (ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})
*/


void   DelayNmSec(INT32U delay);
#endif
