# build all versions

all: wc_single_proc wc_mult_proc wc_mult_procv_shm wc_thread_shmstyle wc_thread flag_wc_thread turn_wc_thread sem_wc_thread sem2_wc_thread

FLAGS=-Wall      \
      -pthread \
      -pedantic

wc_single_proc: wc_single_proc.c
	clang $(FLAGS) -Wall -pedantic -o wc_single_proc wc_single_proc.c

wc_mult_proc: wc_mult_proc.c
	clang $(FLAGS) -o wc_mult_proc wc_mult_proc.c

wc_mult_procv_shm:	wc_mult_proc_shm.c
	clang $(FLAGS) -o wc_mult_proc_shm wc_mult_proc_shm.c

wc_thread_shmstyle: wc_thread_shmstyle.c
	clang $(FLAGS) -o wc_thread_shmstyle wc_thread_shmstyle.c

wc_thread: wc_thread.c
	clang $(FLAGS) -o wc_thread wc_thread.c

flag_wc_thread: flag_wc_thread.c
	clang $(FLAGS) -o flag_wc_thread flag_wc_thread.c

turn_wc_thread: turn_wc_thread.c
	clang $(FLAGS) -o turn_wc_thread turn_wc_thread.c

sem_wc_thread: sem_wc_thread.c
	clang $(FLAGS) -o sem_wc_thread sem_wc_thread.c

sem2_wc_thread: sem2_wc_thread.c
	clang $(FLAGS) -o sem2_wc_thread sem2_wc_thread.c

clean:
	rm -rf wc_single_proc wc_mult_proc wc_mult_proc_shm wc_thread_shmstyle wc_thread
