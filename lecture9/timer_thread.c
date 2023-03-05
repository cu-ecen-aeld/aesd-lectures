
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "time_functions_shared.h"

struct thread_data
{
    /**
    * The number of times the timer_thread has fired
    */
    unsigned int timer_count;

    /**
    * a mutex to use when accessing the structure
    */
    pthread_mutex_t lock;
};

/**
* A thread which runs every timer_period_ms milliseconds
* Assumes timer_create has configured for sigval.sival_ptr to point to the
* thread data used for the timer
*/
static void timer_thread ( union sigval sigval )
{
    struct thread_data *td = (struct thread_data*) sigval.sival_ptr;
    if ( pthread_mutex_lock(&td->lock) != 0 ) {
        printf("Error %d (%s) locking thread data!\n",errno,strerror(errno));
    } else {
        td->timer_count++; 
        if ( pthread_mutex_unlock(&td->lock) != 0 ) {
            printf("Error %d (%s) unlocking thread data!\n",errno,strerror(errno));
        }
    }
}

/**
* Setup the timer at @param timerid (previously created with timer_create) to fire
* every @param timer_period_ms milliseconds, using @param clock_id as the clock reference.
* The time now is saved in @param start_time
* @return true if the timer could be setup successfuly, false otherwise
*/
static bool setup_timer( int clock_id,
                         timer_t timerid, unsigned int timer_period_ms,
                         struct timespec *start_time)
{
    bool success = false;
    if ( clock_gettime(clock_id,start_time) != 0 ) {
        printf("Error %d (%s) getting clock %d time\n",errno,strerror(errno),clock_id);
    } else {
        struct itimerspec itimerspec;
        memset(&itimerspec, 0, sizeof(struct itimerspec));
        itimerspec.it_interval.tv_sec = 0;
        itimerspec.it_interval.tv_nsec = timer_period_ms * 1000000;
        timespec_add(&itimerspec.it_value,start_time,&itimerspec.it_interval);
        if( timer_settime(timerid, TIMER_ABSTIME, &itimerspec, NULL ) != 0 ) {
            printf("Error %d (%s) setting timer\n",errno,strerror(errno));
        } else {
            success = true;
        }
    }
    return success;
}

/**
* Use mutex locking to get the timer count interval for the timer
* using @param td.
* Store the current count value in @param count
* @return true if the count could be obtained
*/
static bool get_timer_count( struct thread_data *td, unsigned int *count )
{
    bool success = false;
    if ( pthread_mutex_lock(&td->lock) != 0 ) {
        printf("Error %d (%s) locking thread data!\n",errno,strerror(errno));
    } else {
        /**
        * Get the timer count in a thread safe way now that mutex is held
        */
        *count = td->timer_count; 
        if ( pthread_mutex_unlock(&td->lock) != 0 ) {
           printf("Error %d (%s) unlocking thread data!\n",errno,strerror(errno));
        } else {
           success = true;
        } 
    }
    return success;
}

/**
* Run a test of the timer at @param timerid setup with clock @param clock_id using timer_create.
* Show it can be used to measure periods of @param timer_period_ms over a sleep duration measured
* by @param sleep_time.  The @param td value is used to calculate the number of timer intervals
* and compare to the expected value.
*/
static bool run_timer_test ( int clock_id, timer_t timerid, 
                        unsigned int timer_period_ms,
                        const struct timespec *sleep_time,
                        struct thread_data *td )
{
    bool success = false;
    struct timespec start_time;
    if ( timer_period_ms == 0 ) {
        printf("Unsupported timer period (must be non-zero)");
    } else {
        if ( setup_timer(clock_id, timerid, timer_period_ms, &start_time) ) {
            struct timespec abstime;
            float sleep_seconds = timespec_to_seconds(sleep_time);
            printf("Sleeping for %f seconds while timer is running once every %u ms\n",
                        sleep_seconds, timer_period_ms);
            timespec_add(&abstime,&start_time,sleep_time);
            if ( clock_nanosleep(clock_id,TIMER_ABSTIME,&abstime,NULL) != 0 ) {
                printf("clock_nanosleep interrupted with errno %d (%s)\n",errno,strerror(errno));
            } else {
                unsigned int timer_count;
                if ( get_timer_count(td,&timer_count) ) {
                    unsigned int expected_timer_count = (sleep_seconds * 1000) / 
                                                                        timer_period_ms;
                    if( timer_count == expected_timer_count ) {
                        printf("Timer count %u matches expected value for sleep time %f seconds "
                                            "and timer period %u ms\n",timer_count,
                                            sleep_seconds,timer_period_ms);
                        success = true;
                    } else {
                        printf("Error; Timer count %u does not match expected value for sleep time %f seconds "
                                            "and timer period %u ms (expecting a count of %u periods)\n",
                                            timer_count,sleep_seconds,timer_period_ms,expected_timer_count);
                    }
                }
            }
        }
    }
    return success;
}

int main ( int argc, char **argv )
{
    struct thread_data td;
    struct sigevent sev;
    bool success = false;
    timer_t timerid;
    memset(&td,0,sizeof(struct thread_data));
    if ( pthread_mutex_init(&td.lock,NULL) != 0 ) {
        printf("Error %d (%s) initializing thread mutex!\n",errno,strerror(errno));
    } else {
        int clock_id = CLOCK_MONOTONIC;
        memset(&sev,0,sizeof(struct sigevent));
        /**
        * Setup a call to timer_thread passing in the td structure as the sigev_value
        * argument
        */
        sev.sigev_notify = SIGEV_THREAD;
        sev.sigev_value.sival_ptr = &td;
        sev.sigev_notify_function = timer_thread;
        if ( timer_create(clock_id,&sev,&timerid) != 0 ) {
            printf("Error %d (%s) creating timer!\n",errno,strerror(errno));
        } else {
            struct timespec sleep_time;
            /**
            * Set sleep time to 2.001 s to ensure the last ms aligned timer event is fired
            */
            sleep_time.tv_sec = 2;
            sleep_time.tv_nsec = 1000000;
            success = run_timer_test(clock_id,timerid,10,&sleep_time,&td);
            if (timer_delete(timerid) != 0) {
                printf("Error %d (%s) deleting timer!\n",errno,strerror(errno));
                success = false;
            }
        }
    }
    return success ? 0 : -1;
}
