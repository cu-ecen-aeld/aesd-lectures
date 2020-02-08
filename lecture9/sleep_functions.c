/**
* @author Dan Walkes
* Sleep related example code
*/
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "time_functions_shared.h"
#include "sleep_args.h"

/**
* Benchmark the sleep time @param sleep_type, sleeping for @param seconds_sleep seconds
* and measuring the actual time slept
* Wait an additional @delay_ms between the clock_gettime call to get the start time for sleeping
* and the actual sleep time.  This will make non absolute time related sleeping less accurate
*/
static bool do_sleep(enum sleep_type sleep_type, float seconds_sleep, unsigned int delay_time_ms)
{
    struct timespec ts_start;
    struct timespec ts_end;
    const int clock_type = CLOCK_MONOTONIC;
    unsigned long microsecond_sleep = (unsigned long)(seconds_sleep * 1000000L);
    struct timespec sleep_time;
    seconds_to_timespec(&sleep_time,seconds_sleep); 
    bool success = false;

    /**
    * Get the starting time before starting sleep
    */
    int rc = clock_gettime(clock_type,&ts_start);
    if( rc != 0 ) {
        printf("Error %d (%s) getting CLOCK_MONOTONIC start time\n",
            errno,strerror(errno));
    } else {
        success = true;
        if( delay_time_ms > 0 ) {
            rc = usleep(delay_time_ms*1000);
            if (rc != 0) {
                printf("usleep interrupted with errno %d in delay (%s)\n",errno,strerror(errno));
                success = false;
            }
        }

        switch (sleep_type)
        {
            case sleep_type_sleep:
            {
                unsigned int ret = sleep(sleep_time.tv_sec);
                if (ret != 0) {
                    printf("sleep interrupted by signal!\n");
                    success = false;
                }
                break;
            }
            case sleep_type_usleep:
            {
                rc = usleep(microsecond_sleep);
                if (rc != 0) {
                    printf("usleep interrupted with errno %d (%s)\n",errno,strerror(errno));
                    success = false;
                }
                break;
            }
            case sleep_type_nanosleep:
            {
                rc = nanosleep(&sleep_time,NULL);
                if (rc != 0) {
                    printf("nanosleep interrupted with errno %d (%s)\n",errno,strerror(errno));
                    success = false;
                }
                break;
            }
            case sleep_type_clock_nanosleep:
            {
                struct timespec abstime;
                struct timespec remaintime;
                timespec_add(&abstime,&ts_start,&sleep_time);
                rc = clock_nanosleep(clock_type,TIMER_ABSTIME,&abstime,&remaintime);
                if (rc != 0) {
                    printf("clock_nanosleep interrupted with errno %d (%s)\n",errno,strerror(errno));
                    success = false;
                }
                break;
            }
            default:
                success = false;
                printf("Unhandled sleep type %d\n",sleep_type);
                break;
        }
        rc = clock_gettime(CLOCK_MONOTONIC,&ts_end);
        if (rc != 0) {
            printf("Error %d (%s) getting CLOCK_MONOTONIC end time\n",
                errno,strerror(errno));
            success = false;
        }
        if (success) {
            struct timespec measured_difference;
            timespec_diff(&measured_difference,&ts_start,&ts_end);
            float measured_seconds = timespec_to_seconds(&measured_difference);
            printf("For sleep type %s, requested sleep time %f seconds actual sleep time %f seconds, difference of %f seconds\n",
                    sleep_type_to_string(sleep_type),seconds_sleep,measured_seconds,measured_seconds-seconds_sleep);
        }
    }
    return success;
}

int main(int argc, char **argv)
{
    struct cmdargs cmdargs;
    bool success = false;
    if( parseargs(&cmdargs,argc,argv) ) {
        enum sleep_type sleep_type;
        success = true;
        for( sleep_type = sleep_type_sleep; sleep_type < sleep_type_unknown; sleep_type ++ ) {
            printf("Sleeping for %f seconds using sleep type %s\n",
                    cmdargs.seconds,sleep_type_to_string(sleep_type));
            if (!do_sleep(sleep_type,cmdargs.seconds,cmdargs.delay_ms)) {
                success = false;
            }
        }
    }

    return success ? 0 : 1;
} 
