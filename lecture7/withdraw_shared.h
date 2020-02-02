/**
* @author Dan Walkes
* Shared ATM withdrawl example code across threading implementations
*/

#ifndef WITHDRAWL_SHARED_H
#define WITHDRAWL_SHARED_H

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
};

extern void do_withdrawls(struct account *account, unsigned int withdraw_request);
#endif
