#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    int rc=-1;
    if( argc < 2 ) {
        printf("Usage: %s filename [nonblock]\n",argv[0]);
        printf("    The file specified as \"filename\" will be created with zero size if it does not exist.\n");
        printf("    If nonblock is specified, the file will be opened in non-blocking mode.\n");
    } else {
        const char *filename = argv[1];
        bool block = true;
        if( argc >= 3 && strncmp(argv[2],"nonblock",8) == 0 ) {
            printf("Using nonblocking mode as specified by argument\n");
            block = false;
        } 
        char buff[1];
        printf("Opening %s in%sblocking mode\n",filename,block ? " " : " non");
        int fd=open(filename,
                O_RDONLY|
                /**
                * When opening in blocking mode, use O_CREAT|O_RDWR to support creating the file if it doesn't exist
                * and to allow opening pipes on Linux when no readers are available (see http://man7.org/linux/man-pages/man7/fifo.7.html)
                * blocking mode.
                */
                block ? O_CREAT|O_RDWR : O_NONBLOCK,
                S_IRWXU|S_IRWXG|S_IRWXO);
        if( fd == -1 ) {
            printf("Error %d (%s) opening %s\n",errno,strerror(errno),filename);
        } else {
            printf("Reading 1 byte from %s\n",filename);
            int readlen = read(fd,buff,1);
            rc = 0;
            if( readlen == -1 ) {
                if( !block && errno == EAGAIN ) {
                    printf("EAGAIN returned from read(), no data available to read\n");
                } else {
                    printf("Error returned from read(), errno is %d (%s)\n",errno,strerror(errno));
                }
                rc = -errno;
            } else {
                if( readlen != 0 ) {
                    printf("Read %d bytes, first byte was %c\n",readlen,buff[0]);
                }
                else {
                    printf("Read 0 bytes (empty file)\n");
                }
            }
            close(fd);
        }
    }
    return rc;
}
