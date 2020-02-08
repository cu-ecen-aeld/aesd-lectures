/**
* @author Dan Walkes
* Sleep argument declarations
*/

#ifndef SLEEP_ARGS_H
#define SLEEP_ARGS_H
#include <stdbool.h>

#define SLEEP_TYPES_LIST \
        SLEEP_TYPE(sleep) \
        SLEEP_TYPE(usleep) \
        SLEEP_TYPE(nanosleep) \
        SLEEP_TYPE(clock_nanosleep) \

#undef SLEEP_TYPE
#define SLEEP_TYPE(type) sleep_type_##type,

enum sleep_type
{
    // will create an enumeration sleep_type_##type for teach type supported
    SLEEP_TYPES_LIST
    sleep_type_unknown
};

/**
* Structure filed by argument parser
*/
struct cmdargs {
    /**
    * The number of seconds to sleep
    */
    float  seconds;
    /**
    * The number of milliseconds to delay between clock_gettime and sleep
    */
    unsigned int delay_ms;
};

const char *sleep_type_to_string( enum sleep_type type );
extern void printusage( const char *progname );
extern bool parseargs( struct cmdargs *args, int argc, char **argv );
#endif
