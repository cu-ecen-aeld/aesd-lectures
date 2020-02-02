/**
* @author Dan Walkes
* Withdraw argument parsing functions
*/

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include "withdraw_args.h"

#define STARTING_BALANCE_DEFAULT 10000
#define WITHDRAW_REQUEST_DEFAULT 100
#define NUM_THREADS_DEFAULT      5


void printusage( const char *progname )
{
    printf("Usage : %s [ --safe ] [ --starting_balance BALANCE ] [ --withdraw_request AMOUNT ] [ --num_threads N ]\n",progname);
    printf("    --safe                          use locking on withdrawls for thread safe implementation\n");
    printf("    --starting_balance BALANCE      use BALANCE as starting account balance (default %u)\n",STARTING_BALANCE_DEFAULT);
    printf("    --withdraw_request AMOUNT       use AMOUNT for each withdraw request (default %u)\n",WITHDRAW_REQUEST_DEFAULT);
    printf("    --num_threads      N            use N threads (default %u)\n",NUM_THREADS_DEFAULT);
}

/**
* Parse arguments in @param argc and @param argv, placing results or
* defaults into the structure at @param args
* @return true if parsing completed successfully, false if a failure occurred
*/ 
bool parseargs( struct cmdargs *args, int argc, char **argv )
{
    int safe_flag = 0;
    const struct option long_options[] =
    {
        {"safe",     no_argument,       &safe_flag, 1},
        {"help",     no_argument,       0, 'h'},
        {"starting_balance", required_argument,       0, 's'},
        {"withdraw_request", required_argument,       0, 'w'},
        {"num_threads", required_argument,       0, 'n'},
        {0, 0, 0, 0}
    };
    int rc = 0;
    bool success = true;
    memset(args,0,sizeof(struct cmdargs));
    args->starting_balance = STARTING_BALANCE_DEFAULT;
    args->withdraw_request = WITHDRAW_REQUEST_DEFAULT;
    args->num_threads = NUM_THREADS_DEFAULT;
    args->locking = ACCOUNT_LOCKING_NONE;
    do {
        int option_index = 0;
        rc = getopt_long(argc,argv,"hs:w:n",long_options,&option_index);
        if ( rc != -1 ) {
            switch ( rc ) {
                case 0:
                    break;
                case 's':
                    args->starting_balance = atoi(optarg);
                    printf("Using starting balance %u\n",args->starting_balance);
                    break;
                case 'w':
                    args->withdraw_request = atoi(optarg);
                    printf("Using withdraw_request %u\n",args->withdraw_request);
                    break;
                case 'n':
                    args->num_threads= atoi(optarg);
                    if ( args->num_threads <= 0 ) {
                        printf("invalid number of threads specified: %d\n",args->num_threads);
                        success = false;
                    } else {
                        printf("Using num_threads%u\n",args->num_threads);
                    }
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
    if ( success && safe_flag ) {
        args->locking = ACCOUNT_LOCKING_MUTEX;
    }
    return success;
}
