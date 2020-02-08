
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <getopt.h>
#include "sleep_args.h"

#define NUM_SECONDS_DEFAULT              1
#define DELAY_MILLISECONDS_DEFAULT       0

void printusage( const char *progname )
{
    printf("Usage : %s [ --seconds SECONDS ] [ --interrupt MILLISEC ]\n",progname);
    printf("    --seconds SECONDS         wait SECONDS seconds in sleep (default %d)\n",NUM_SECONDS_DEFAULT);
    printf("    --delay MILLISEC          simulate an delay of MILISEC milliseconds (default %d)\n",DELAY_MILLISECONDS_DEFAULT);
    printf("                              between clock_gettime and sleep starts.\n");
    printf(" Sleeps the number of seconds specified for each supported sleep type\n");
    printf(" and measures the total time slept, optionally including a delay between clock_gettime and\n");
}

/**
* @return a string describing the enumerated sleep type @param type
*/
const char *sleep_type_to_string(enum sleep_type type)
{
    const char *rtnstring = "Unknown";
    switch(type) {
#undef SLEEP_TYPE
#define SLEEP_TYPE(type) case sleep_type_##type: \
                            rtnstring = #type; \
                            break; \

                    // build a list of enumerated types, setting return string based on type 
                    SLEEP_TYPES_LIST
                            
                    default:
                        break;
    }
    return rtnstring;
} 

/**
* @return the enumerated type corresponding to string @param type_string, or sleep_type_unknown
* if the string does not match
*/
enum sleep_type sleep_type_from_string(const char *type_string)
{
    enum sleep_type sleep_type;
    for( sleep_type = sleep_type_sleep; sleep_type < sleep_type_unknown; sleep_type ++ ) {
        if (strcmp(sleep_type_to_string(sleep_type),type_string) == 0 ) {
           break;
       }
    }
    return sleep_type;
}

/**
* Parse arguments in @param argc and @param argv, placing results or
* defaults into the structure at @param args
* @return true if parsing completed successfully, false if a failure occurred
*/ 
bool parseargs( struct cmdargs *args, int argc, char **argv )
{
    const struct option long_options[] =
    {
        {"help",     no_argument,       0, 'h'},
        {"seconds", required_argument,       0, 's'},
        {"delay", required_argument,       0, 'd'},
        {0, 0, 0, 0}
    };
    int rc = 0;
    bool success = true;
    memset(args,0,sizeof(struct cmdargs));
    args->seconds = NUM_SECONDS_DEFAULT;
    args->delay_ms = DELAY_MILLISECONDS_DEFAULT;
    do {
        int option_index = 0;
        rc = getopt_long(argc,argv,"hs:t:",long_options,&option_index);
        if ( rc != -1 ) {
            switch ( rc ) {
                case 0:
                    break;
                case 's':
                    args->seconds = strtof(optarg,NULL);
                    printf("Sleeping for %f seconds.\n",args->seconds);
                    break;
                case 'd':
                    args->delay_ms = strtoul(optarg,NULL,0);
                    printf("Delaying for %d milliseconds between clock_gettime and sleep call.\n",args->delay_ms);
                    break;
                case 'h':
                    success = false;
                    break;
                case '?':
                    success = false;
                    break;
                default:
                    success = false;
                    break;
            }
        }
    } while ( success && rc != -1 );
    if( !success ) {
        printusage(argv[0]);
    }
    return success;
}
