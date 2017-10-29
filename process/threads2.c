#include <stdio.h>
#include <assert.h>
#include <pthread.h>

long count = 0;
int thread_ids[3] = {0,1,2};

void *inc_count(void *t) {
 	int i;
 	long my_id = (long)t;
	printf("I am a counter %ld\n", my_id);
	for (i = 0; i < 1e7; i++) {
		count = count + 1;
	}
 	sleep(1);
 	pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
 	int i;
 	long t1=1, t2=2, t3=3;

 	pthread_t threads[3];
 	pthread_attr_t attr;

 	pthread_attr_init(&attr);

	pthread_create(&threads[0], &attr, inc_count, (void *)t1);
 	pthread_create(&threads[1], &attr, inc_count, (void *)t2);
 	pthread_create(&threads[2], &attr, inc_count, (void *)t3);

 	for (i=0; i<3; i++) {
 		pthread_join(threads[i], NULL);
 	}

	printf("count %ld\n", count);
 	pthread_exit(NULL);
}
