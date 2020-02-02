/**
* @author Dan Walkes
* Shared withdrawl functions for AESD
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "withdraw_shared.h"

/**
* Simulate disbursing @param amount on our fictional ATM
*/
static void disburse_money(unsigned int amount)
{
    printf("Disbursing $%u\n",amount);
}

/**
* Withdraw @param amount from @param account
* @return true if the withdrawl was successful and money was disbursed
* @return false if the account does not contain enough to complete the
* transaction
*/
static bool withdraw( struct account *account, unsigned int amount )
{
    const int balance = account->current_balance;
    if (balance >= amount) {
        account->current_balance = balance - amount;
        disburse_money(amount);
        account->withdrawl_total += amount;
        return true;
    }
    return false;
}

/**
* Do withdrawls on the account specified by @param account in @param withdraw_request
* increments until the account does not have enough remaining to complete the withdrawl
*/
void do_withdrawls(struct account *account, unsigned int withdraw_request)
{
    bool withdraw_success=false;
    do {
        withdraw_success = withdraw(account,withdraw_request);
    } while(withdraw_success);  
}

