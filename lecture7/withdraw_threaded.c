/**
* @author Dan Walkes
* Multithreaded withdrawl example for AESD
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "withdraw_shared.h"
#include <stdlib.h>
#include <pthread.h>
/**
* A struture used to start threads for the withdrawl example
*/
struct withdraw_threadparams
{
    /**
    * A pointer to the account used for this thread
    */
    struct account *account;
    /**
    * The amount to request in each withdrawl on this thread
    */
    unsigned int withdraw_request;
};

/**
* The entry point for each thread for use with POSIX threading
* @param arg - pointer to a withrdaw_threadparams structure (cast to void *)
* @return - the parameter passed as arg
*/
static void *start_withdrawl_thread (void *arg)
{
    struct withdraw_threadparams *params=(struct withdraw_threadparams*)arg;
    do_withdrawls(params->account,params->withdraw_request);
    return arg;
}

/**
* Starts @param num_threads withdrawl threads on @param account, each
* requesting @param withdraw_request dollars per transaction.  Waits for
* all threads to complete.
* @return true if one or more threads couldn't be started successfully.
*/
static bool run_withdrawl_threads(struct account *account, 
                        unsigned int withdraw_request,
                        unsigned int num_threads)
{
    bool success = false;
    /**
    * An array of pointer to dynamically allocated pthread structures
    */
    pthread_t **thread_array;
    thread_array=malloc(sizeof(pthread_t*)*num_threads);
    if ( thread_array == NULL ) {
        printf("Memory allocation for pthread pointer failed\n");
    } else { 
        success = true; 
        struct withdraw_threadparams params;
        unsigned int thread;
        memset(&params,0,sizeof(struct withdraw_threadparams));
        params.account=account;
        params.withdraw_request=withdraw_request;
        for ( thread = 0; thread < num_threads; thread++ ) {
            thread_array[thread] = (pthread_t *) malloc(sizeof(pthread_t));
            if ( thread_array[thread] == NULL ) {
                printf("Memory allocation failure for thread array entry failed\n");
                success = false;
            } else {
                int rc = pthread_create(thread_array[thread],
                                    NULL, // Use default attributes
                                    start_withdrawl_thread,
                                    &params);
                if ( rc != 0 ) {
                    printf("pthread_create failed with error %d creating thread %u\n",rc,thread);
                    success = false;
                }
                printf("Started thread %d with id %ld\n",thread,(unsigned long int)*thread_array[thread]);
            }
        }
        for ( thread = 0; thread < num_threads; thread++ ) {
            if ( thread_array[thread] != NULL ) {
                int rc = pthread_join(*thread_array[thread],NULL);
                if( rc != 0 ) {
                    printf("Attempt to pthread_join thread %u failed with %d\n",thread,rc);
                    success=false;
                }
                free(thread_array[thread]);
            }
        }
        free(thread_array);
    }
    return success;
}

int main(int argc, char **argv)
{
    const int starting_balance=1000;
    const unsigned int withdraw_request=100;
    const int num_threads=2;
    struct account useraccount;

    withdraw_account_init(&useraccount,starting_balance);
 
    if ( run_withdrawl_threads(&useraccount,withdraw_request,num_threads) ) {
        if ( useraccount.withdrawl_total > starting_balance ) {
            printf("Withdrew a total of $%u from an account which only contained $%u!\n",
                        useraccount.withdrawl_total,starting_balance);
            return -1;
        } else {
            printf("Withdrew a total of $%u from account which contained $%u\n",
                        useraccount.withdrawl_total,starting_balance);
            return 0;
        }
    } else {
        printf("Error starting withdrawl threads\n");
        return -1;
    }
}
