#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h> // strtoul
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    int rc=-1;
    if( argc != 3 ) {
        printf("Usage: %s filename size\n",argv[0]);
        printf("    Create a file \"filename\" with size \"size\" bytes, or\n");
        printf("    extend an existing file by \"size\" bytes.\n");
    } else {
        const char *filename=argv[1];
        long int size = strtol(argv[2],NULL,0);
        int fd=open(filename,
                O_CREAT|O_RDWR,
                S_IRWXU|S_IRWXG|S_IRWXO);
        if( fd == -1 ) {
            printf("Error %d (%s) opening %s\n",errno,strerror(errno),filename);
        }
        else {
            off_t ret=lseek(fd,(off_t)size,SEEK_END);
            if( ret == -1 ) {
                printf("Error from lseek, errno was %d (%s)\n",errno,strerror(errno));
            }
            else {
                uint32_t value=0;
                ssize_t bytes_written = write(fd,&value,sizeof(value));
                if( bytes_written == -1 ) {
                    printf("Error from write, errno was %d (%s)\n",errno,strerror(errno));
                } else if ( bytes_written != sizeof(value) ) {
                    printf("Unexpected short write of %zd (expected %d bytes)\n",bytes_written,value);
                } else {
                    printf("Created sparse file %s with size %ld\n",filename,size);
                    rc = 0;
                }
            }
        }
    }
    return rc;
}
