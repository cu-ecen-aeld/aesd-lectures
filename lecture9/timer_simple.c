/**
* @author Dan Walkes
* Signal handling example code
*/

#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <unistd.h> // pause, alarm()

bool caught_sigalarm = false;

static void signal_handler ( int signal_number )
{
    int errno_saved = errno;
    if ( signal_number == SIGALRM ) {
        caught_sigalarm = true;
    }
    errno = errno_saved;
}

int main ( int argc, char **argv )
{
    struct sigaction new_action;
    bool success = true;
    memset(&new_action,0,sizeof(struct sigaction));
    new_action.sa_handler=signal_handler;
    if( sigaction(SIGALRM, &new_action, NULL) != 0 ) {
        printf("Error %d (%s) registering for SIGALRM",errno,strerror(errno));
        success = false;
    }
    if( success ) {
        alarm(2); 
        printf("Waiting 2 seconds for alarm signal\n");
        pause();
        if( caught_sigalarm ) {
            printf("Caught SIGALARM!\n");
        } else {
            printf("Error: Did not catch SIGALARM!\n");
            success = false;
        }
    }
    return  success ? 0 : 1;
}
