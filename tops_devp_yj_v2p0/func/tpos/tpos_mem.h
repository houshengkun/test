#ifndef __TOPSCOMM_DEVP_TOPS_MEM_H__
#define __TOPSCOMM_DEVP_TOPS_MEM_H__

#include "tpos_data_type.h"

//Get offset address of a member in a structure.
//����ṹ���Ա�����ڽṹ���еĵ�ַƫ����
#ifndef offsetof
#define offsetof(type,member) ((unsigned int)&((type*)0)->member)
#endif

//Get structure pointer from it's member
//�ӽṹ���Ա������ַ��ȡ�ṹ���ַ
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
