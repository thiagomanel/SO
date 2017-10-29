#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
	//how to write "hellow world" using two processes?
    pid_t pid, donep;
    pid = 0;
    pid = fork();
    if (pid == 0) {
	write(1, "hello ", 6);
	exit(0);
    } else {
	donep = wait(0);
	write(1, "world\n", 6);
        return 0;
    }
}

