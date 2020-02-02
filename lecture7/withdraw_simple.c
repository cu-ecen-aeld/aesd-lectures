/**
* @author Dan Walkes
* Simple withdrawl example for AESD
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "withdraw_shared.h"

int main(int argc, char **argv)
{
    const int starting_balance=1000;
    const unsigned int withdraw_request=100;
    struct account useraccount;

    withdraw_account_init(&useraccount,starting_balance);

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
