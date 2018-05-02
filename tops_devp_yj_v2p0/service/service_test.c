#include "app.h"
#include "service_test.h"
#include "tpos_data_type.h"
#include "drv_rs232.h"

INT8U task_result = 1;
void * task_test(void * param)
{
    //INT8U buffer[10] = "ABCDEFG";
    INT8U buffer[10] = {0xDE,0xDE,0xDE,0xDE,0xAA,0x55};
    printf("...............1111..........\n");

    drv_uart_init(USART_ID_2,9600,USART_8E1);
    printf("going...\n");
    sleep(30);
    printf("continue...\n");
    drv_uart_read_buffer(USART_ID_2,buffer,6);
    drv_uart_send_buffer(USART_ID_2,buffer,6,NULL);

    return &task_result;
}
