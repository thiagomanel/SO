These snippets support learning execution flows (processes vs threads)

All the programs have the same objective: to count words in text files under a root directory.
Under this root dir we have a collection of subdirectories. Under each one of these subdirs, we have text files.

wc_single_proc.c    - This program process the whole dataset, using a single process.
wc_mult_proc.c      - This program uses multiple processes to process the dataset. The parent process creates a new process to each one of the subdirectories. This program is buggy (on purpose). It highlights child processes have a copy of parents memory. Then, we need explicitly communicate with parent to send the partial word count
wc_mult_proc_shm.c  - This program solves the bug of the previous one by communicating through shared memory
wc_thread_shmstyle.c - This program uses multiple threads to process the dataset. It emulates the program style found on the above programs
wc_thread_shmstyle.c - This program takes advantage threads share the same address space to simplify the code shown in the wc_thread_shmstyle.c program. (beware, it has a bug; again, on purpose)


To build above programs, type *make*

To generate the dataset, type *bash ./make_dataset*

To execute above programs, type *./program_name dataset*

