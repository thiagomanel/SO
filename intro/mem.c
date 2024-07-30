#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//cc -o mem mem.c -Wl,-no_pie
int main(int argc, char *argv[]) {
    int *p = malloc(sizeof(int)); // a1
    printf("(%d) address pointed to by p: %p\n",
		getpid(), p); // a2
    *p = atoi(argv[1]);       // a3
    while (1) {
        sleep(1);
	*p = *p + 1;
	printf("(%d) p: %d\n", getpid(), *p); // a4
    }
    return 0;
}
