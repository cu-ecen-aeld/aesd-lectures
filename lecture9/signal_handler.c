/**
* @author Dan Walkes
* Signal handling example code
*/

#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <unistd.h> // pause

bool caught_sigint = false;
bool caught_sigterm = false;

static void signal_handler ( int signal_number )
{
    if ( signal_number == SIGINT ) {
        caught_sigint = true;
    } else if ( signal_number == SIGTERM ) {
        caught_sigterm = true;
    }
}

int main ( int argc, char **argv )
{
    struct sigaction new_action;
    bool success = true;
    memset(&new_action,0,sizeof(struct sigaction));
    new_action.sa_handler=signal_handler;
    if( sigaction(SIGTERM, &new_action, NULL) != 0 ) {
        printf("Error %d (%s) registering for SIGTERM",errno,strerror(errno));
        success = false;
    }
    if( sigaction(SIGINT, &new_action, NULL) ) {
        printf("Error %d (%s) registering for SIGINT",errno,strerror(errno));
        success = false;
    }

    if( success ) {
        printf("Waiting forever for a signal\n");
        pause();
        if( caught_sigint ) {
            printf("\nCaught SIGINT!\n");
        }
        if( caught_sigterm ) {
            printf("\nCaught SIGTERM!\n");
        }
    }
    return  success ? 0 : 1;
}
