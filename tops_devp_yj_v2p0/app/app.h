#ifndef APP_H
#define APP_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "tpos_data_type.h"

#define MAX_TASKS 10

void APP_Tasks (void);

#endif // APP_H
