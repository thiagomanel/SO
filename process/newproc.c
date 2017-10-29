#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
    char *argv[3];
    int xpto = 0;
    argv[0]  = "ps";
    argv[1] = "xau";
    argv[2] = NULL;
    pid_t pid, donep;
    pid = 0;
    pid = fork();
    if (pid == 0) {
    	printf("Upon successful completion, fork() returns a value of 0 to the child process %d\n", getpid());
	xpto = 1;
	printf("child dying %d\n", xpto);
	//execv("/bin/ps", argv);
	exit(0);
    } else {
        printf("Upon successful completion, fork() returns returns the process ID of the child process to the parent process %d\n", getpid());
	donep = wait(0);
	printf("child %d %d has gone\n", donep, xpto);
        return 0;
    }
}

