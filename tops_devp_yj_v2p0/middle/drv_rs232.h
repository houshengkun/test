#ifndef DRV_RS232_H
#define DRV_RS232_H

#include "tpos_data_type.h"

typedef enum {

    USART_8N1 = 0x00,
    USART_8E1 = 0x01,
    USART_8O1 = 0x02,
    USART_9N1 = 0x03,
    USART_8N2 = 0x04,
    USART_8E2 = 0x05,
    USART_8O2 = 0x06,
    USART_9N2 = 0x07

} USART_LINECONTROL_MODE;

typedef enum {
    USART_ID_1 = 0,
    USART_ID_2,
    USART_ID_3,
    USART_ID_4,
    USART_ID_5,
    USART_ID_6,
    USART_ID_7,
    USART_ID_8,
    USART_ID_9,
    USART_ID_10,
    USART_NUMBER_OF_MODULES

} USART_MODULE_ID;


#ifdef PC
#define USART_PREFIX "/dev/ttyUSB"
#else
#define USART_PREFIX "/dev/ttymxc"
#endif

INT16S drv_uart_read_byte(USART_MODULE_ID usart_id);
INT16S drv_uart_read_buffer(USART_MODULE_ID usart_id, INT8U *recv_buff, INT16U read_len);
INT8S drv_uart_send_buffer(USART_MODULE_ID usart_id, INT8U *data, INT16U len, INT8U *state);
INT8S drv_uart_init(USART_MODULE_ID usart_id,INT32U baudRate,USART_LINECONTROL_MODE uartMode);

#endif // DRV_RS232_H
