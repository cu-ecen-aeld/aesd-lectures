/*
* Brief - A simple program that demonstrates the working of pthread_cancel()
*/
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static void *threadFunc(void *arg)
{
    printf("Thread: threadFunc started\n");

    //Enters an infinite loop and thus the thread does not terminate on its own
    while(1){
        sleep(1);
        printf("\nthreadFunc: executing loop\n");
    }

    printf("\nThread: threadFunc exiting now\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t t1_id;
    int s, count;

    printf("\nMain thread started:\n");
    s = pthread_create(&t1_id, NULL, threadFunc, NULL);
    if (s != 0)
        perror("pthread_create error");

    for(count = 0 ; count < 10 ; count ++){
        sleep(2);
        printf("\n    Main thread: count value = (%d)\n",count);
    }

    pthread_cancel(t1_id); //Used to terminate/cancel the thread t1

    printf("Main Thread exiting now\n");
    
    return 0;
}



