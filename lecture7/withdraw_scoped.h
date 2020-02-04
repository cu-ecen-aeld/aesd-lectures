/**
* @author Dan Walkes
* Scoped mutex example
* Based on Linux System Programming Chapter 7
*/

#ifndef WITHDRAW_SCOPED_H
#define WITHDRAW_SCOPED_H
#ifdef __cplusplus

#include <pthread.h>
#include "withdraw_shared.h"

class ScopedMutex {
    public:
        ScopedMutex (pthread_mutex_t &mutex)
            :mutex(mutex)
        {
            int rc = pthread_mutex_lock(&mutex);
            if ( rc != 0 ) {
                printf("Attempt to obtain mutex failed with %d\n",rc);
            }
        }

        ~ScopedMutex ()
        {
            int rc = pthread_mutex_unlock(&mutex);
            if ( rc != 0 ) {
                printf("Attempt to unlock mutex failed with %d\n",rc);
            }
        }

    private: 
        pthread_mutex_t &mutex;
};

static inline bool withdraw_scoped( struct account *account, unsigned int amount )
{
    bool success = false;
    { // create a scope for the scoped mutex.  Mutex will be held within this scope
        ScopedMutex lock(account->mutex);
        const int balance = account->current_balance;
        if ( balance >= (long) amount ) {
            success = true;
            printf("Withdrawl approved\n");
            account->current_balance = balance - amount;
            account->withdrawl_total += amount;
        }
    }
    if ( success ) {
        disburse_money(amount);
    }
    return success;
}

#else // !__cplusplus

static inline bool withdraw_scoped( struct account *account, unsigned int amount )
{
    printf("scoped withdrawls are only supported on C++ builds\n");
    return false;
}

#endif
#endif
