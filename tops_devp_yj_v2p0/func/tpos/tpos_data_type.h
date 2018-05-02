/* 
 * File:   base_data_type.h
 * Author: Administrator
 * Desc: can be imported to compile firmware/software which runing on 32 or 64 bit platform
 *
 * Created on 2014?9?5?, ??10:57
 */

#ifndef __TOPSCOMM_DEVP_BASE_DATA_TYPE_H__
#define	__TOPSCOMM_DEVP_BASE_DATA_TYPE_H__

#ifdef	__cplusplus
extern "C" {
#endif

typedef unsigned char    BOOLEAN;
typedef unsigned char    INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char    INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short   INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short   INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned int     INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   int     INT32S;                   /* Signed   32 bit quantity                           */
typedef unsigned long long   INT64U;               /* Unsigned 64 bit quantity                           */
typedef signed  long long   INT64S;                /* Signed   64 bit quantity                           */
typedef float            FP32;                     /* Single precision floating point                    */
typedef long double      FP64;                     /* Double precision floating point                    */

typedef unsigned int OS_STK;
typedef unsigned int *OS_EVENT_HANDLE;     //实际存放一个数据地址
typedef unsigned int OS_EVENT;
typedef unsigned int OS_TICK10MS;   //10ms 延时数量


#ifndef TRUE
#define TRUE  0x01
#endif

#ifndef FALSE
#define FALSE 0x00
#endif


#ifndef NULL
 #define NULL   0UL
#endif

#ifndef PIN_HIGH
#define PIN_HIGH                1      //高电平
#endif
#ifndef PIN_LOW
#define PIN_LOW                 0      //低电平
#endif

#ifdef	__cplusplus
}
#endif

#define STRUCT_OFFSET(struct_object,e) (unsigned long)&(((struct_object*)0)->e)
#endif	/* __TOPSCOMM_DEVP_BASE_DATA_TYPE_H__ */

