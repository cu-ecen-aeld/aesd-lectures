/*
* Brief - A simple program that demonstrates the usage of pthread_detach()
*
* If a joinable thread is not joined by calling pthread_join(), then the terminated thread becomes a Zombie thread,
* and continues to consume system resources.
*
* If pthread_detach() is used the system automatically cleans up terminated thread, and there is no need to join the thread using pthread_join()
*/
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define SLEEP_DURATION_SECONDS                              10

static void *threadFunc(void *arg)
{

    printf("Thread: threadFunc started\n");

    pthread_detach(pthread_self());

    sleep(SLEEP_DURATION_SECONDS);
    printf("\nThread: threadFunc exiting now\n");

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t t1_id;
    int s;

    s = pthread_create(&t1_id, NULL, threadFunc, NULL);
    if (s != 0)
        perror("pthread_create error");


    printf("Main Thread exiting now\n");
    pthread_exit(NULL);
}



