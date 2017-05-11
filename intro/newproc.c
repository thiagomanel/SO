#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = 0;
    pid = fork();
    if (pid == 0) {
    	printf("Upon successful completion, fork() returns a value of 0 to the child process\n");
    } else {
        printf("Upon successful completion, fork() returns returns the process ID of the child process to the parent process.\n");
        return 0;
    }
}

