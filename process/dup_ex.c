#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
	int fd;
	fd = dup(1);
	write(1, "hello ", 6);
	write(fd, "world\n", 6);
}

