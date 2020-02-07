/** * @author Dan Walkes
* Time related example code
*/
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define CLOCKLIST \
        CLOCKLIST_ENTRY(CLOCK_REALTIME)\
        CLOCKLIST_ENTRY(CLOCK_MONOTONIC)\
        CLOCKLIST_ENTRY(CLOCK_PROCESS_CPUTIME_ID)\
        CLOCKLIST_ENTRY(CLOCK_THREAD_CPUTIME_ID)

/**
* Print the clock time for the clock with id @param id and name
* @param clocktype and return in @param ts
*/
bool print_clock_time( clockid_t id, const char *clocktype, struct timespec *ts )
{
    bool success = false;
    int rc = clock_gettime(id,ts);
    if( rc != 0 ) {
        printf("Error %d (%s) getting clock %d (%s) time\n",
                errno,strerror(errno),id,clocktype);
    } else {
        printf("Clock %d (%s) %ld.%09ld\n",id,clocktype,ts->tv_sec,ts->tv_nsec);
        success = true;
    }
    return success;
}

static void print_time_difference( const struct timespec *ts_start, const struct timespec *ts_end, const char *clocktype)
{
    printf("Clock %s difference between start and end times was %ld.%09ld seconds\n",
                clocktype,
                ts_end->tv_sec-ts_start->tv_sec,
                ts_end->tv_nsec > ts_start->tv_nsec ? ts_end->tv_nsec - ts_start->tv_nsec :
                                                      1000000000-ts_start->tv_nsec + ts_end->tv_nsec);
}

int main ( int argc, char **argv )
{
    struct timespec ts_realtime_start;
    struct timespec ts_monotonic_start;
    struct timespec ts_process_cputime_start;
    struct timespec ts_thread_cputime_start;
    bool success = false;
    printf("Time at start:\n");
    if ( print_clock_time(CLOCK_REALTIME,"CLOCK_REALTIME",&ts_realtime_start) &&
        print_clock_time(CLOCK_MONOTONIC,"CLOCK_MONOTONIC",&ts_monotonic_start) &&
        print_clock_time(CLOCK_PROCESS_CPUTIME_ID,"CLOCK_PROCESS_CPUTIME_ID",&ts_process_cputime_start) &&
        print_clock_time(CLOCK_THREAD_CPUTIME_ID,"CLOCK_THREAD_CPUTIME_ID",&ts_thread_cputime_start) ) {
        struct tm tm;
        if ( gmtime_r(&ts_realtime_start.tv_sec,&tm) == NULL ) {
            printf("Error calling gmtime_r with time %ld\n",ts_realtime_start.tv_sec);
        } else  {
            char result[100];
            // print in RFC 822 compilant date format
            if( strftime(result,sizeof(result),"%a, %d %b %y %T %z",&tm) == 0 ) {
                printf("Error converting string with strftime\n");
            } else {
                success = true;
                printf("Current date in RFC822 compliant date format: %s\n",result);
            }
        }
    }
    if ( success ) {
        struct timespec ts_realtime_end;
        struct timespec ts_monotonic_end;
        struct timespec ts_process_cputime_end;
        struct timespec ts_thread_cputime_end;
        printf("Time at end:\n");
        if ( print_clock_time(CLOCK_REALTIME,"CLOCK_REALTIME",&ts_realtime_end) &&
            print_clock_time(CLOCK_MONOTONIC,"CLOCK_MONOTONIC",&ts_monotonic_end) &&
            print_clock_time(CLOCK_PROCESS_CPUTIME_ID,"CLOCK_PROCESS_CPUTIME_ID",&ts_process_cputime_end) &&
            print_clock_time(CLOCK_THREAD_CPUTIME_ID,"CLOCK_THREAD_CPUTIME_ID",&ts_thread_cputime_end) ) {
            printf("Per-clock time delay:\n");
            print_time_difference(&ts_realtime_start,&ts_realtime_end,"CLOCK_REALTIME");
            print_time_difference(&ts_monotonic_start,&ts_monotonic_end,"CLOCK_MONOTONIC");
            print_time_difference(&ts_process_cputime_start,&ts_process_cputime_end,"CLOCK_PROCESS_CPUTIME_ID");
            print_time_difference(&ts_thread_cputime_start,&ts_thread_cputime_end,"CLOCK_THREAD_CPUTIME_ID");
        }
    }

    return success ? 0 : 1;
} 
