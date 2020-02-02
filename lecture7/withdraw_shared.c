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
/**
* Simulate disbursing @param amount on our fictional ATM
*/
static void disburse_money(unsigned int amount)
{
    printf("Disbursing $%u from thread %lu\n",amount,(unsigned long int)pthread_self());
}

/**
* Withdraw @param amount from @param account
* @return true if the withdrawl was successful and money was disbursed
* @return false if the account does not contain enough to complete the
* transaction
*/
static bool withdraw( struct account *account, unsigned int amount )
{
    bool success = true;
    const int balance = account->current_balance;
    if (balance < amount) {
        success = false;
    } else {
        printf("Withdrawl approved\n");
        account->current_balance = balance - amount;
        account->withdrawl_total += amount;
    }
    if ( success ) {
        disburse_money(amount);
    }
    return success;
}

/**
* Initialize @param account with starting balance @param starting_balance
*/
void withdraw_account_init(struct account *account, unsigned int starting_balance)
{
    memset(account,0,sizeof(struct account));
    account->current_balance=starting_balance;
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
