/**
* @author Dan Walkes
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
* @param clocktype
*/
void print_clock_time( clockid_t id, const char *clocktype )
{
    struct timespec ts;
    int rc = clock_gettime(id,&ts);
    if( rc != 0 ) {
        printf("Error %d (%s) getting clock %d (%s) time\n",
                errno,strerror(errno),id,clocktype);
    } else {
        printf("Clock %d (%s) %ld.%ld\n",id,clocktype,ts.tv_sec,ts.tv_nsec);
    }
}

int main ( int argc, char **argv )
{
    printf("Time at start:\n");
     // turn a list of clock entries into a list of function calls, passing the type as a string in the second argument
    #define CLOCKLIST_ENTRY(entry)  print_clock_time(entry,#entry);
    CLOCKLIST 
   
    struct timespec ts;
    struct tm tm;
    int rc = clock_gettime(CLOCK_REALTIME,&ts);
    bool success = false;
    if( rc != 0 ) {
        printf("Error %d (%s) getting CLOCK_REALTIME time\n",
                errno,strerror(errno));
    } else {
        if ( gmtime_r(&ts.tv_sec,&tm) == NULL ) {
            printf("Error calling gmtime_r with time %ld\n",ts.tv_sec);
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
    printf("Time at end:\n");
    CLOCKLIST 
 
    return success ? 0 : 1;
} 
