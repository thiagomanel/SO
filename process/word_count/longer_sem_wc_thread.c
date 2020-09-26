#include <ctype.h>
#include <dirent.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>           
#include <sys/stat.h>
#include <semaphore.h>

#define MAX_ANSWERS 1024

struct thread_param {
  char *dir_path;
};

sem_t *mutex;
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
  char *file_content = NULL;
  long length;

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

  DIR *dir;
  struct dirent *ent;
  char *filepath;
  size_t count;

  dir = opendir(dir_path);
  if (dir) {
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_type == DT_REG) { // if is regular file
        filepath = malloc(strlen(dir_path) + strlen(ent->d_name) + 2);
        sprintf(filepath, "%s/%s", dir_path, ent->d_name);
        count = wc_file(filepath);
        sem_wait(mutex);
        WC_COUNT += count;
	sleep(1);
        sem_post(mutex);
        free(filepath);
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
    
  mutex = sem_open("/mutex", O_CREAT, 0644, 1);
  WC_COUNT = 0;

  size_t n_threads = 0;
  pthread_t threads[MAX_ANSWERS];
  struct thread_param params[MAX_ANSWERS];

  root_dir = opendir(root_path);

  if (root_dir) {
    while ((ent = readdir(root_dir)) != NULL) {
      if (ent->d_type == DT_DIR) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
          filepath[n_threads] = malloc(strlen(root_path) + strlen(ent->d_name) + 2);
          sprintf(filepath[n_threads], "%s/%s", root_path, ent->d_name);
          params[n_threads].dir_path = filepath[n_threads];
          pthread_create(&threads[n_threads], NULL, wc_dir, (void *)&params[n_threads]);
          n_threads++;
        }
      }
    }
    closedir(root_dir);
  }

  for (size_t i = 0; i < n_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  sem_close(mutex);
  sem_unlink("/mutex");
  printf("%zu\n", WC_COUNT);
  pthread_exit(NULL);
}
