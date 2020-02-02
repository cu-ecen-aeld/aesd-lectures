/**
* @author Dan Walkes
* Shared ATM withdrawl example code across threading implementations
*/

#ifndef WITHDRAWL_SHARED_H
#define WITHDRAWL_SHARED_H

#include <pthread.h>

/**
* The type of locking to use for withdrawls (for demonstration purposes)
*/
enum withdraw_locking {
    ACCOUNT_LOCKING_NONE= 0,  // unsafe implementation for demonstration purposes
    ACCOUNT_LOCKING_MUTEX = 1, // use a lock and unlock mutex approach
};

/**
* A structure representing a fictional bank account for withdrawls
*/
struct account {
    /**
    * The current balance of the account
    */
    int current_balance;
    /**
    * The total of approved withdrawls on the account
    */
    unsigned int withdrawl_total; 
  
    /**
    * The mutex used to lock this account when manipulating values, for thread safety
    */ 
    pthread_mutex_t mutex;

    /**
    * The type of locking we use when interacting with the account
    * (for demonstration purposes)
    */
    enum withdraw_locking locktype;
};

extern bool withdraw_account_init(struct account *account, unsigned int starting_balance, enum withdraw_locking locktype);
extern void do_withdrawls(struct account *account, unsigned int withdraw_request);
#endif
