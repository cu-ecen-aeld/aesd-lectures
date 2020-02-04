/**
* @author Dan Walkes
* Shared withdrawl functions for AESD
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "withdraw_shared.h"
#include "withdraw_scoped.h"

/**
* Simulate disbursing @param amount on our fictional ATM
*/
void disburse_money(unsigned int amount)
{
    printf("Disbursing $%u from thread %lu\n",amount,(unsigned long int)pthread_self());
}

/**
* Non thread-safe implementation of withdraw, using no locking
*/
static bool withdraw_unsafe( struct account *account, unsigned int amount )
{
    bool success = false;
    const int balance = account->current_balance;
    if ( balance >= (long) amount ) {
        success = true;
        printf("Withdrawl approved\n");
        account->current_balance = balance - amount;
        account->withdrawl_total += amount;
        disburse_money(amount);
    }
    return success;
}

/**
* Thread safe implementation of withdraw() using mutexes
*/
static bool withdraw_mutex( struct account *account, unsigned int amount )
{
    bool success = false;
    int rc = pthread_mutex_lock(&account->mutex);
    if ( rc != 0 ) {
        printf("pthread_mutex_lock failed with %d\n",rc);
    } else {
        const int balance = account->current_balance;
        if ( balance >= (long) amount ) {
            success = true;
            printf("Withdrawl approved\n");
            account->current_balance = balance - amount;
            account->withdrawl_total += amount;
        }
        rc = pthread_mutex_unlock(&account->mutex);
        if ( rc != 0 ) {
            printf("pthread_mutex_unlock failed with %d\n",rc);
            success = false; // not sure if we should give out cash in this case, error on the safe side...
        }
        if ( success ) {
            disburse_money(amount);
        }
    }
    return success;
}

/**
* Withdraw @param amount from @param account, using specified locking
* set in the account structure.
* @return true if the withdrawl was successful and money was disbursed
* @return false if the account does not contain enough to complete the
* transaction
*/
static bool withdraw( struct account *account, unsigned int amount )
{
    bool success = false;
    switch ( account->locktype ) {
        case ACCOUNT_LOCKING_NONE:
            success = withdraw_unsafe(account,amount);
            break;
        case ACCOUNT_LOCKING_MUTEX:
            success = withdraw_mutex(account,amount);
            break;
        case ACCOUNT_LOCKING_SCOPED:
            success = withdraw_scoped(account,amount);
            break;
        default:
            printf("Unhandled locking type %d in withdraw function\n",account->locktype);
            break;
    }
    return success;
}
/**
* Initialize @param account with starting balance @param starting_balance
* Use @param locktype when performing account transactions
* @return true when initialized successfully, false if failed to initialize
*/
bool withdraw_account_init(struct account *account, unsigned int starting_balance,enum withdraw_locking locktype)
{
    int rc = 0;
    bool success = true;
    memset(account,0,sizeof(struct account));
    account->current_balance=starting_balance;
    account->locktype = locktype;
    rc = pthread_mutex_init(&account->mutex,NULL);
    if ( rc != 0 ) {
        printf("Failed to initialize account mutex, error was %d",rc);
        success = false;
    }
    return success; 
}

/**
* Do withdrawls on the account specified by @param account in @param withdraw_request
* increments until the account does not have enough remaining to complete the withdrawl
* Assumes the @param account structure has been previously initialized with @param withdraw_account_init
*/
void do_withdrawls(struct account *account, unsigned int withdraw_request)
{
    bool withdraw_success=false;
    do {
        withdraw_success = withdraw(account,withdraw_request);
    } while(withdraw_success);  
}
