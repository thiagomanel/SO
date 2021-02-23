#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
	char estado = 'p';
    	int child_pid;

	system("ps -f");
    	printf("processo %d: criando processo filho\n", getpid());
    	child_pid = fork();
	system("ps -f");
    	printf("processo %d: fork retornou %d\n", getpid(), child_pid);
    	if (child_pid == 0) estado = 'f';
    	printf("processo %d: o valor da variável estado deste processo é: %c\n", getpid(), estado);
}
