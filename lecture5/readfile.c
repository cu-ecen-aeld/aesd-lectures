#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
    int rc=-1;
    if( argc != 2 ) {
        printf("Usage: %s filename\n",argv[0]);
        printf("    The file specified as \"filename\" will be created with zero size if it does not exist.\n");
    } else {
        const char *filename = argv[1];
        int fd=open(filename,
                O_RDWR|O_CREAT,
                S_IRWXU|S_IRWXG|S_IRWXO);
        char buff[1];
        if( fd == -1 ) {
            printf("Error opening %s\n",filename);
        } else {
            int readlen = read(fd,buff,1);
            rc = 0;
            if( readlen == -1 ) {
                printf("Error with read(), errno is %d (%s)\n",errno,strerror(errno));
                rc = -1;
            }
            if( readlen != 0 ) {
                printf("read %d bytes, first byte was %c\n",readlen,buff[0]);
            }
            else {
                printf("Read 0 bytes (empty file)\n");
            }
            close(fd);
        }
    }
    return rc;
}
