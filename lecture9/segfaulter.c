/**
* @author Dan Walkes
* segfaulting file
*/

int main( int argc, char **argv )
{
    int *mem=0x0;
    // oops!  segfault here
    *mem = *mem + 1;
    return 0;
}

