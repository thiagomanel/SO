#include <ctype.h>
#include <dirent.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_ANSWERS 1024

struct thread_param {
  size_t thread_id;
  char *dir_path;
};

size_t N_THREADS;
size_t TURN;
size_t WC_COUNT;

size_t wc(const char *content) {
  size_t count = 0;

  for (bool inword = false; *content; ++content) {
    if (isspace(*content)) {
      if (inword) {
        inword = false;
      }
    } else {
      if (!inword) {
        inword = true;
        ++count;
      }
    }
  }
  return count;
}

size_t wc_file(const char *filename) {
  char *file_content = 0; // how to init? 0 or null?
  long length;            // what is the modern typ?

  FILE *f = fopen(filename, "rb");

  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    file_content = malloc(length);
    if (file_content) {
      fread(file_content, 1, length, f);
    }
    fclose(f);

    return wc(file_content);
  }

  return -1;
}

// count words in file within dir_path
// we do not walk in subdirs
void *wc_dir(void *t) {
  struct thread_param *param = (struct thread_param*) t;
  char *dir_path = param->dir_path;
  size_t thread_id = param->thread_id;
  fprintf(stderr, "thread[%zu]:%s\n", thread_id, dir_path);

  DIR *dir;
  struct dirent *ent;
  char filepath[1024]; // unsafe
  size_t count;

  dir = opendir(dir_path);
  if (dir) {
    // printf("pid %d dir %s\n", getpid(), root_path);
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_type == DT_REG) { // if is regular file
        sprintf(filepath, "%s/%s", dir_path, ent->d_name);
	count = wc_file(filepath);
	fprintf(stderr, "thread[%zu]: TURN[%zu]\n", thread_id, TURN);
	while (TURN != thread_id)
           ;
        WC_COUNT += count;
        if (++TURN == N_THREADS) TURN = 0;
      }
    }
  }
  closedir(dir);

  pthread_exit(NULL);
}

// it calculates the number of words in files
// stored under directory argv[1]
//
// we assume a depth 3 hierarchy.
// At level 1, we have the root
// at level 2, we have subdirs
// at level 3, we have files
//
// root--
//       |-- subdir-1
//       |-- subdir-2
//       |-- ...
//       |-- subdir-3
int main(int argc, char *argv[argc + 1]) {

  DIR *root_dir;
  struct dirent *ent;
  char *filepath[MAX_ANSWERS];
  char *root_path = argv[1];

  WC_COUNT = 0;
  TURN = MAX_ANSWERS + 1;

  N_THREADS = 0;
  pthread_t threads[MAX_ANSWERS];
  struct thread_param params[MAX_ANSWERS];

  root_dir = opendir(root_path);

  if (root_dir) {
    while ((ent = readdir(root_dir)) != NULL) {
      if (ent->d_type == DT_DIR) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
          filepath[N_THREADS] = malloc(strlen(root_path)+strlen(ent->d_name)+2);
          sprintf(filepath[N_THREADS], "%s/%s", root_path, ent->d_name);
          params[N_THREADS].dir_path = filepath[N_THREADS];
          params[N_THREADS].thread_id = N_THREADS;
          pthread_create(&threads[N_THREADS], NULL, wc_dir, (void *)&params[N_THREADS]);
          N_THREADS++;
	}
      }
    }
    TURN = 0;
    closedir(root_dir);
  }

  for (size_t i = 0; i < N_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("%zu\n", WC_COUNT);
  pthread_exit(NULL);
}
