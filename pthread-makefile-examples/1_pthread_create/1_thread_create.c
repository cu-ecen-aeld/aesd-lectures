/*
* Brief - A simple example that demonstrates the creation a pthread.
*
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Thread function should have return type (void *) and should receive arguments of type (void *)
static void * threadFunc(void *arg)
{

    char *str = (char *) arg;

    //On execution, note that that PID of this thread is the same as that of pthread
    printf("ThreadFunc: arguments passed to thread are: %s , pid = (%d)\n", str,getpid());
    (void)sleep(2);
    printf("\nthreadFunc: exiting now\n");
    return(0);
}

int main(int argc, char *argv[])
{
    /* At this point the process has only one thread, i.e main thread. */ 
    pthread_t t1;
    void *res;
    int s;

    /* Create a thread with,
    * First parameter holds the thread ID when the thread is created
    * The second parameter is NULL, indicating that the thread is created wih default attributes
    * The third parameter is a function pointer from which the thread begins execution 
    * The last parameter is the arguments that needs to be passed to the thread function*/

    s = pthread_create(&t1, NULL, threadFunc, "Hello world");

    if (s != 0)
        perror("Thread create error");

    
    printf("main thread: Message from main() , pid = (%d)\n",getpid());

    sleep(5);
    printf("\nmain thread: exiting now\n");

    exit(0);
}
