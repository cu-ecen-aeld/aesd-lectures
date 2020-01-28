#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
	bool parent = true;
	int childexec = 0;
	pid_t pid = fork();
	if ( pid == 0 ) {
		parent = false;
		childexec++;
	}
	printf("Hello from %s\n",parent ? "parent" : "child");
	if( parent ) {
		printf("Child pid is %d\n",pid);
	}
	printf("childexec is %d from %s thread\n",childexec,parent ? "parent" : "child");
}
