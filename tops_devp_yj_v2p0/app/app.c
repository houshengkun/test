#include "app.h"
#include "service_test.h"
#include "tpos_data_type.h"

void APP_Tasks (void)
{
    INT8U * pthread_return;
    INT8U pthread_result = 0;
    pthread_t tid[MAX_TASKS] = {0};

    pthread_create(&tid[0],NULL,task_test,NULL);

    pthread_result = pthread_join(tid[0],&pthread_return);

    if(pthread_result != 0)
    {
        printf("Thread join failed!\n");
    }
    printf("Thread return value : %d .",*pthread_return);
}

