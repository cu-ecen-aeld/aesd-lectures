/**
* @author Dan Walkes
* Time functions shared between multiple implementations
*/

#ifndef TIME_FUNCTIONS_SHARED_H
#define TIME_FUNCTIONS_SHARED_H
#include <time.h>

/**
* Set @param result with the value of @param ts_start - @param ts_end, handling
* rollover, assuming @param ts_end is after @param ts_start
*/
static inline void timespec_diff( struct timespec *result,
                        const struct timespec *ts_start, const struct timespec *ts_end)
{
    result->tv_sec = ts_end->tv_sec - ts_start->tv_sec;
    if ( ts_end->tv_nsec < ts_start->tv_nsec ) {
        result->tv_nsec = 1000000000L - ts_start->tv_nsec + ts_end->tv_nsec;
        result->tv_sec--;
    } else {
        result->tv_nsec = ts_end->tv_nsec - ts_start->tv_nsec;
    }
}

/**
* Set @param result with a timespec representing @param float seconds
*/
static inline void seconds_to_timespec( struct timespec *result, float seconds)
{
    float nanoseconds;
    result->tv_sec = (time_t) seconds;
    nanoseconds = seconds - result->tv_sec;
    result->tv_nsec = (long) (nanoseconds * 1000000000L);
}

/**
* @return a float representation in seconds of the timespect at @param ts
*/
static inline float timespec_to_seconds( const struct timespec *ts )
{
    return ts->tv_sec + (((float)ts->tv_nsec) / 1000000000L);
}

/**
* set @param result with @param ts_1 + @param ts_2
*/
static inline void timespec_add( struct timespec *result,
                        const struct timespec *ts_1, const struct timespec *ts_2)
{
    result->tv_sec = ts_1->tv_sec + ts_2->tv_sec;
    result->tv_nsec = ts_1->tv_nsec + ts_2->tv_nsec;
    if( result->tv_nsec > 1000000000L ) {
        result->tv_nsec -= 1000000000L;
        result->tv_sec ++;
    }
}
#endif
