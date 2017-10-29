#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    //it is equivalent to "cat < foo.txt"
    char *argv[2];
    argv[0] = "cat";
    argv[1] = NULL;
    pid_t pid, donep;
    pid = 0;
    pid = fork();
    if (pid == 0) {
    	printf("Upon successful completion, fork() returns a value of 0 to the child process\n");
	close(0);
	open("newproc.c", O_RDONLY);
	execv("/bin/cat", argv);
	exit(0);
    } else {
	donep = wait(0);
	printf("child %d has gone\n", donep);
        return 0;
    }
}

