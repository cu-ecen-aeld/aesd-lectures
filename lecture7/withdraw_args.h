/**
* @author Dan Walkes
* Withdraw argument parsing functions
*/

#ifndef WITHDRAW_ARGS_H
#define WITHDRAW_ARGS_H

#include <stdbool.h>
#include "withdraw_shared.h"
/**
* Structure filed by argument parser
*/
struct cmdargs {
    /**
    * Starting balance to use with account
    */
    int starting_balance;
    /**
    * Amount to withdraw from each request
    */
    unsigned int withdraw_request;
    /**
    * Number of threads to use for withdrawls
    */
    unsigned int num_threads;
    /**
    * Locking to use for withdrawls
    */
    enum withdraw_locking locking;
};

extern void printusage( const char *progname );
extern bool parseargs( struct cmdargs *args, int argc, char **argv );

#endif
