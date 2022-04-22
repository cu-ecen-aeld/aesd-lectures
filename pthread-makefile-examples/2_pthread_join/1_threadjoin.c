/*
* Brief - A simple program that demostrates pthread_join()
*/
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define SLEEP_DURATION_SECONDS                          10

static void *threadFunc(void *arg)
{
    printf("Thread: threadFunc started\n");

    sleep(SLEEP_DURATION_SECONDS);
    printf("\nThread: threadFunc exiting now\n");

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t t1_id;
    void *res;
    int s;

    s = pthread_create(&t1_id, NULL, threadFunc, NULL);
    if (s != 0)
        perror("pthread_create error");

    s = pthread_join(t1_id, &res); // pthread_join() blocks until the thread specified in first parameter completes execution

    if (s != 0)
        perror("pthread_join error");
    printf("main thread: Thread returned %s\n",(char *) res);


    printf("Main Thread exiting now\n");
    pthread_exit(NULL);
}



