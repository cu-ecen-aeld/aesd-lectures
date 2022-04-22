/*
* Brief - A simple example that demonstrates thread creation and termination
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static void * threadFunc(void *arg)
{
    char *s = (char *) arg;
    printf("ThreadFunc: %s , printed in threadFunc pid = (%d)\n", s,getpid());
    (void)sleep(15);
    printf("\nthreadFunc: exiting now\n");

    pthread_exit(0); //pthread_exit is used to terminate a thread
}

int main(int argc, char *argv[])
{
    pthread_t t1;
    void *res;
    int s;

    s = pthread_create(&t1, NULL, threadFunc, "Hello world");
    if (s != 0)
        perror("Thread create error");
    printf("main thread: Message from main() , pid = (%d)\n",getpid());

    sleep(5);
    printf("\nmain thread: after sleep 5 sec\n");

    // exit(0); //If exit is called from main thread, it kills all the created threads as it terminates the process
    pthread_exit(0); //pthread_exit() is called from the main thread, this ensures that all the other threads in this process continue to execute until termination
}
