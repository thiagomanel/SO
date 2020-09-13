#include <ctype.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_FILE "/tmp/shm_wc"
#define MAX_ANSWERS 1024

// the processes will share this Response on the shared memory
typedef struct Response {
  size_t answers[MAX_ANSWERS];
} Response;

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
size_t wc_dir(const char *dir_path) {

  DIR *dir;
  struct dirent *ent;
  char filepath[1024]; // unsafe

  size_t count = 0;

  dir = opendir(dir_path);
  if (dir) {
    // printf("pid %d dir %s\n", getpid(), root_path);
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_type == DT_REG) { // if is regular file
        sprintf(filepath, "%s/%s", dir_path, ent->d_name);
        count += wc_file(filepath);
      }
    }
  }
  closedir(dir);
  return count;
}

int init_shm() {
  // the shared memory is backed by a file, we need to create it
  FILE *f;
  f = fopen(SHM_FILE, "w");
  fclose(f);
  return 0;
}

key_t generate_key() {
  key_t key = ftok(SHM_FILE, 666);
  if (key == -1) {
    perror("ftok error");
    return -1;
  }
  return key;
}

int generate_mem_segment_id(key_t key) {
  int shmid;
  shmid = shmget(key, sizeof(Response), 0777 | IPC_CREAT);
  if (shmid == -1) {
    perror("shmge error");
    return -1;
  }
  return shmid;
}

int destroy_shm() {
  key_t key = generate_key();
  int shm_id = generate_mem_segment_id(key);
  shmctl(shm_id, IPC_RMID, NULL);
  return 0;
}

// attach to the shared memory identified by shmid
int attach_mem_segment_id(int shmid, Response **response) {
  void *shm = shmat(shmid, (void *)0, 0);
  if (shm == (void *)(-1)) {
    perror("error on shmat");
    return -1;
  }
  *response = shm;
  return 0;
}

int attach(Response **response) {
  // we need a key to access the shm region
  key_t key = generate_key();
  if (key == -1) {
    return key;
  }

  // the shm memory region has an id
  int shmid = generate_mem_segment_id(key);
  if (shmid == -1) {
    return shmid;
  }

  return attach_mem_segment_id(shmid, response);
}

int detach(Response *response) {
  if (shmdt(response) == -1) {
    perror("error on detaching shared mem");
  }

  return 0;
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
  char filepath[1024]; // unsafe
  char *root_path = argv[1];

  size_t count = 0;
  size_t child_count = 0;

  pid_t wpid;
  int status;

  init_shm();
  // we will collect answer on this Response object, living on the shared memory
  Response *shm_response;
  if (attach(&shm_response) == -1) {
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < MAX_ANSWERS; i++) {
    shm_response->answers[i] = 0;
  }

  root_dir = opendir(root_path);

  if (root_dir) {
    // printf("pid %d dir %s\n", getpid(), root_path);
    while ((ent = readdir(root_dir)) != NULL) {
      if (ent->d_type == DT_DIR) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
          sprintf(filepath, "%s/%s", root_path, ent->d_name);

          if (fork() == 0) {
            Response *child_response;
            if (attach(&child_response) == -1) {
              perror("error attaching child\n");
            }
            child_response->answers[child_count] = wc_dir(filepath);
            detach(child_response);
            exit(0);
          }

          // we need a counter to the children know where to write in the vector
          ++child_count;
        }
      }
    }
    closedir(root_dir);

    status = 0;
    while ((wpid = wait(&status)) > 0)
      ;
  }

  for (size_t i = 0; i < child_count; i++) {
    count += shm_response->answers[i];
  }

  printf("%zu\n", count);
  destroy_shm();

  return EXIT_SUCCESS;
}
