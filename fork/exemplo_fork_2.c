#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
	char estado = 'p';
	int my_pid = getpid();
    	int child_pid;

    	printf("%d: processos antes da criação do processo filho\n", my_pid);
	system("ps -f");
    	printf("%d: criando processo filho\n", my_pid);
	if ((child_pid = fork()) == 0) {
        	printf("%d: minha cópia de pid ainda tem o id de meu pai: %d\n", getpid(), my_pid);
        	my_pid = getpid();
        	printf("%d: o valor da variável estado no processo filho é: %c\n", my_pid, estado);
        	printf("%d: filho está aguardando uma entrada do teclado\n", my_pid);
		estado = getchar();
	} else {
        	printf("%d: processos depois da criação do processo filho\n", my_pid);
		system("ps -f");
        	printf("%d: pai está esperando pelo filho: %d\n", my_pid, child_pid);
		wait(&child_pid);
	}
    	printf("%d: terminando com o valor da variável estado igual a: %c\n", my_pid, estado);
}
