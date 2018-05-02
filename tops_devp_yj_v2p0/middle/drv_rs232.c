#include "app.h"
#include "drv_rs232.h"

INT32S usart_fd[USART_NUMBER_OF_MODULES] = {0};//descriptor of serial port device
/**
 * @brief drv_uart_open
 * @param pathname
 * @param flags
 * @return -1:fail
 */
INT32S drv_uart_open(char *pathname, INT32S flags)
{
    INT32S fd = -1;

    if(pathname == NULL)
        return -1;

    if(flags == 0)
    {
        flags = O_RDWR | O_NOCTTY | O_NDELAY;
    }

    // open the device
    fd = open(pathname, flags);
    if(fd == -1)
    {
        printf("Failed to open uart %s\n", pathname);
        return -1;
    }

    return fd;
}
/**
 * @brief drv_uart_close
 * @param usart_id
 */
void drv_uart_close(USART_MODULE_ID usart_id)
{
    INT8S result = 0;
    if(usart_fd[usart_id] > 0)
    {
        result = close(usart_fd[usart_id]);
        if(result == 0)
        {
            usart_fd[usart_id] = 0;
        }
        else
        {
            printf("Close uart %s%u failure!", USART_PREFIX, usart_id);
        }
    }
}

/**
 * @brief drv_uart_set
 * @param fd
 * @param baud_rate
 * @param uart_mode
 * @return 0:success,-1:fail
 */
INT32S drv_uart_set(INT32S fd, INT32U baud_rate, USART_LINECONTROL_MODE uart_mode)
{
    struct termios     options;
    INT8U              bits = 0;
    INT8U              parity = 'N';
    INT8U              stop = 1;
   // struct sigaction   saio;

    memset(&options, 0, sizeof(options));

    if(tcgetattr(fd, &options) < 0)
    {
        printf("UART: tcgetarrt error\n");
    }

    // 设置串口波特率，输入和输出速率要一致
    switch(baud_rate)
    {
        case 50:
            cfsetispeed(&options, B50);
            cfsetospeed(&options, B50);
            break;
        case 75:
            cfsetispeed(&options, B75);
            cfsetospeed(&options, B110);
            break;
        case 10:
            cfsetispeed(&options, B134);
            cfsetispeed(&options, B150);
            break;
        case 134:
            cfsetispeed(&options, B134);
            cfsetospeed(&options, B134);
            break;
        case 150:
            cfsetispeed(&options, B150);
            cfsetispeed(&options, B150);
            break;
        case 200:
            cfsetispeed(&options, B200);
            cfsetispeed(&options, B200);
            break;
        case 300:
            cfsetispeed(&options, B300);
            cfsetispeed(&options, B300);
            break;
        case 600:
            cfsetispeed(&options, B600);
            cfsetispeed(&options, B600);
            break;
        case 1200:
            cfsetispeed(&options, B1200);
            cfsetispeed(&options, B1200);
            break;
        case 1800:
            cfsetispeed(&options, B1800);
            cfsetospeed(&options, B1800);
            break;
        case 2400:
            cfsetispeed(&options, B2400);
            cfsetospeed(&options, B2400);
            break;
        case 4800:
            cfsetispeed(&options, B4800);
            cfsetospeed(&options, B4800);
            break;
        case 9600:
            cfsetispeed(&options, B9600);
            cfsetospeed(&options, B9600);
            break;
        case 115200:
            cfsetispeed(&options, B115200);
            cfsetospeed(&options, B115200);
            break;
        case 460800:
            cfsetispeed(&options, B460800);
            cfsetospeed(&options, B460800);
            break;
        default:
            printf("Unkown baud_rate!\n");
            return -1;
    }

    // 设置控制模式
    options.c_cflag |= CLOCAL;   // 保证程序不占用串口
    options.c_cflag |= CREAD;    // 保证程序可以从串口读取数据

    switch(uart_mode)
    {
    case 0:
        bits = 8;
        parity = 'N';
        stop = 1;
        break;
    case 1:
        bits = 8;
        parity = 'E';
        stop = 1;
        break;
    case 2:
        bits = 8;
        parity = 'O';
        stop = 1;
        break;
    default:
        bits = 8;
        parity = 'N';
        stop = 1;
        break;
    }

    // 设置数据位
    switch(bits)
    {
        case 5:
            options.c_cflag &= ~CSIZE;  //屏蔽其他标志位
            options.c_cflag |= CS5;
            break;
        case 6:
            options.c_cflag &= ~CSIZE; //屏蔽其他标志位
            options.c_cflag |= CS6;
            break;
        case 7:
            options.c_cflag &= ~CSIZE; //屏蔽其他标志位
            options.c_cflag |= CS7;
            break;
        case 8:
            options.c_cflag &= ~CSIZE; //屏蔽其他标志位
            options.c_cflag |= CS8;
            break;
        default:
            printf("Unkown bits!\n");
            return -1;
    }

     /* 设置奇偶校验 */
    switch(parity)
    {
        /*无奇偶校验位*/
        case 'n':
        case 'N':
            options.c_cflag &= ~PARENB;
            break;
        /*设置奇校验*/
        case 'o':
        case 'O':
            options.c_cflag |= PARENB;//PARENB：产生奇偶位，执行奇偶校验
            options.c_cflag |= PARODD;//PARODD：若设置则为奇校验,否则为偶校验
            options.c_cflag |= INPCK;//INPCK：使奇偶校验起作用
            options.c_cflag |= ISTRIP;//ISTRIP：若设置则有效输入数字被剥离7个字节，否则保留全部8位
            break;
        /*设置偶校验*/
        case 'e':
        case 'E':
            options.c_cflag |= PARENB;//PARENB：产生奇偶位，执行奇偶校验
            options.c_cflag &= ~PARODD;//PARODD：若设置则为奇校验,否则为偶校验
            options.c_cflag |= INPCK;//INPCK：使奇偶校验起作用
            options.c_cflag |= ISTRIP;//ISTRIP：若设置则有效输入数字被剥离7个字节，否则保留全部8位
            break;
        default:
            printf("Unkown parity!\n");
            return -1;
    }

    /*设置停止位*/
    switch(stop)
    {
        case 1:
            options.c_cflag &= ~CSTOPB;//CSTOPB：使用两位停止位
            break;
        case 2:
            options.c_cflag |= CSTOPB;//CSTOPB：使用两位停止位
            break;
        default:
            printf("Unkown stop!\n");
            return -1;
    }

    options.c_iflag &= ~(ICRNL | IXON);
    /*设置输出模式为原始输出*/
    options.c_oflag &= ~OPOST;//OPOST：若设置则按定义的输出处理，否则所有c_oflag失效

    /*设置本地模式为原始模式*/
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    /*设置等待时间和最小接受字符*/
    options.c_cc[VTIME] = 0;//可以在select中设置
    options.c_cc[VMIN] = 1;//最少读取一个字符

    /*如果发生数据溢出，只接受数据，但是不进行读操作*/
    tcflush(fd,TCIFLUSH);

    /*激活配置*/
    if(tcsetattr(fd,TCSANOW,&options) < 0)
    {
        perror("tcsetattr failed");
        return -1;
    }

    return 0;
}

/**
 * @brief drv_uart_init
 * @param usart_id
 * @param baudRate
 * @param uartMode
 * @return TRUE:success,FALSE:fail
 */
INT8S drv_uart_init(USART_MODULE_ID usart_id,INT32U baudRate,USART_LINECONTROL_MODE uartMode)
{
    char usart_dev_name[48] = {0};

    if(usart_id > USART_NUMBER_OF_MODULES)//cant open the undefined uart port
    {
        return FALSE;
    }

    if(usart_id == USART_ID_1)            //USART_ID_1 is used as a debug terminal
    {
        return FALSE;
    }

    sprintf(usart_dev_name, "%s%u", USART_PREFIX, usart_id);

    usart_fd[usart_id] = drv_uart_open(usart_dev_name, 0);
    if(usart_fd[usart_id] < 0)
    {
        printf("Failed to open uart: %s\n", usart_dev_name);
        return FALSE;
    }

    printf("drv_uart_init:uart dev name:%s,baud_rate:%d,mode:%d\n",usart_dev_name, baudRate, uartMode);

    drv_uart_set(usart_fd[usart_id], baudRate, uartMode);

    return TRUE;
}
/**
 * @brief drv_uart_send_buffer
 * @param usart_id
 * @param data
 * @param len
 * @param state
 * @return 0:SUCCESS,-1:FAIL
 */
INT8S drv_uart_send_buffer(USART_MODULE_ID usart_id, INT8U *data, INT16U len, INT8U *state)
{
    /*
    *state=APP_FRAME_SEND_ONGOING;
    dma_rs233_channel[4].app_state=state;
    dma_rs233_channel[4].send_len=len;
    dma_rs233_channel[4].send_buffer=data;
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_5_TRANSMIT);
    */

    INT16U n_left = len;
    INT32S n_written = -1;
    INT8U  try_times = 0;
    INT8U  *ptr = data;
    INT32U i = 0;
    INT32S usart_fd_current = 0;

    if(usart_id > USART_NUMBER_OF_MODULES)//cant comm with the undefined uart port
    {
        printf("cant comm with the undefined uart port %s%u.", USART_PREFIX, usart_id);
        return -1;
    }

    if(usart_id == USART_ID_1)            //USART_ID_1 is used as a debug terminal
    {
        printf("USART_ID_1 is used as a debug terminal.");
        return -1;
    }

    if(usart_fd[usart_id] > 0)
    {
        usart_fd_current = usart_fd[usart_id];
    }
    else
    {
        printf("Don't have a valid uart port(%s%u) file descriptor!", USART_PREFIX, usart_id);
        return -1;
    }

    while((n_left > 0) && (try_times ++ < 10))
    {
        if ((n_written = write(usart_fd_current, ptr, n_left)) <= 0)
        {
            if(n_written < 0 && errno == EINTR)
            {
                printf("Error %d occured.Detailed info: %s.\n Uart(%s%u) write operation will be attempted again.\n", errno, strerror(errno),USART_PREFIX, usart_id);
                n_written = 0;
            }
            else
            {
                printf("Error %d occured.Detailed info: %s.\n Uart(%s%u) write operation was canceled.\n", errno, strerror(errno),USART_PREFIX, usart_id);
                return -1;
            }
        }

        n_left -= n_written;
        ptr += n_written;
    }

    if(n_left == 0)
    {
        printf("uart(%s%u)  write success:\n",USART_PREFIX, usart_id);
        for(i = 0; i < len; i ++)
        {
            printf("%x ", data[i]);
        }
        printf("\n");

        return 0;
    }
    else
    {
        printf("uart(%s%u)  write fail!\n",USART_PREFIX, usart_id);
        return -1;
    }
}
/**
 * @brief drv_uart_read_buffer
 * @param usart_id
 * @param recv_buff
 * @param read_len
 * @return -1:read failure,0:no data was received,>0:the number of datas were received.
 */
INT16S drv_uart_read_buffer(USART_MODULE_ID usart_id, INT8U *recv_buff, INT16U read_len)
{
    INT32S n_read = 0,usart_fd_current = 0;

    if(usart_id > USART_NUMBER_OF_MODULES)//cant comm with the undefined uart port
    {
        printf("cant comm with the undefined uart port %s%u.", USART_PREFIX, usart_id);
        return -1;
    }

    if(usart_id == USART_ID_1)            //USART_ID_1 is used as a debug terminal
    {
        printf("USART_ID_1 is used as a debug terminal.");
        return -1;
    }

    if(usart_fd[usart_id] > 0)
    {
        usart_fd_current = usart_fd[usart_id];
    }
    else
    {
        printf("Don't have a valid uart port(%s%u) file descriptor!", USART_PREFIX, usart_id);
        return -1;
    }

    n_read = read(usart_fd_current, recv_buff, read_len);

    if(n_read <= 0 )
    {
        return n_read;
    }

    //printf("rs485_read: has data, n_read:%d\n", n_read);
    return n_read;
}
/**
 * @brief drv_uart_read_byte
 * @param usart_id
 * @return -1:unvalid data.
 */
INT16S drv_uart_read_byte(USART_MODULE_ID usart_id)
{
    INT8U data = 0;
    if(1 == drv_uart_read_buffer(usart_id,&data,1))
    {
        return data;
    }
    else
    {
        return -1;
    }
}
