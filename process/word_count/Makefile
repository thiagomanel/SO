# build all versions

all: wc_single_proc wc_mult_proc wc_mult_procv_shm wc_thread_shmstyle wc_thread flag_wc_thread turn_wc_thread tsl_wc_thread longer_tsl_wc_thread sem_wc_thread longer_sem_wc_thread

FLAGS=-Wall      \
      -pthread \
      -pedantic

wc_single_proc: wc_single_proc.c
	gcc $(FLAGS) -Wall -pedantic -o wc_single_proc wc_single_proc.c

wc_mult_proc: wc_mult_proc.c
	gcc $(FLAGS) -o wc_mult_proc wc_mult_proc.c

wc_mult_procv_shm:	wc_mult_proc_shm.c
	gcc $(FLAGS) -o wc_mult_proc_shm wc_mult_proc_shm.c

wc_thread_shmstyle: wc_thread_shmstyle.c
	gcc $(FLAGS) -o wc_thread_shmstyle wc_thread_shmstyle.c

wc_thread: wc_thread.c
	gcc $(FLAGS) -o wc_thread wc_thread.c

flag_wc_thread: flag_wc_thread.c
	gcc $(FLAGS) -o flag_wc_thread flag_wc_thread.c

turn_wc_thread: turn_wc_thread.c
	gcc $(FLAGS) -o turn_wc_thread turn_wc_thread.c

tsl_wc_thread: tsl_wc_thread.c
	gcc $(FLAGS) -o tsl_wc_thread tsl_wc_thread.c

longer_tsl_wc_thread: longer_tsl_wc_thread.c
	gcc $(FLAGS) -o longer_tsl_wc_thread longer_tsl_wc_thread.c

sem_wc_thread: sem_wc_thread.c
	gcc $(FLAGS) -o sem_wc_thread sem_wc_thread.c

longer_sem_wc_thread: longer_sem_wc_thread.c
	gcc $(FLAGS) -o longer_sem_wc_thread longer_sem_wc_thread.c

clean:
	rm -rf wc_single_proc wc_mult_proc wc_mult_proc_shm wc_thread_shmstyle wc_thread flag_wc_thread turn_wc_thread tsl_wc_thread longer_tsl_wc_count sem_wc_thread longer_sem_wc_thread

