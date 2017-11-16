#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main() {
  printf("Pre-forking...\n");
  
  int child1 = fork();
  int child2 = 0;
  if (child1) {
    child2 = fork();
  }
  if (!child2) {
    srand(time(NULL));
    int random = (rand() % 16) + 5;
    
    if (!child1) {
      printf("random 1: %d\n", random);
      sleep(random);
    }
    else {
      random = (rand() % 16) + 5;
      printf("random 2: %d\n", random);
      sleep(random);
    }
    printf("Child PID: %d\nDone\n", getpid());
    return random;
  }
  else {
    int *status;
    wait(status);
    printf("status: %d\n", *status);
  }

  return 0;
}
