#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

/**
* Simulate disbursing @param amount on our fictional ATM
*/
void disburse_money(unsigned int amount)
{
    printf("Disbursing $%u\n",amount);
}

/**
* Withdraw @param amount from @param account
* @return true if the withdrawl was successful and money was disbursed
* @return false if the account does not contain enough to complete the
* transaction
*/
bool withdraw( struct account *account, unsigned int amount )
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

int main(int argc, char **argv)
{
    const int starting_balance=1000;
    const unsigned int withdraw_request=100;
    struct account useraccount;
    memset(&useraccount,0,sizeof(struct account));
    useraccount.current_balance = starting_balance; 
    
    do_withdrawls(&useraccount,withdraw_request);

    if( useraccount.withdrawl_total > starting_balance ) {
        printf("Withdrew a total of $%u from an account which only contained $%u!\n",
                    useraccount.withdrawl_total,starting_balance);
        return -1;
    } else {
        printf("Withdrew a total of $%u from account which contained $%u\n",
                    useraccount.withdrawl_total,starting_balance);
        return 0;
    }
}
