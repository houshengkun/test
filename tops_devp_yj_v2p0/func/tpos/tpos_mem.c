#include "tpos_mem.h"
#include "stdio.h"

//精度只能达到10ms，因此最小值为10
void DelayNmSec(INT32U delay)
{
    sleep(delay);
}


