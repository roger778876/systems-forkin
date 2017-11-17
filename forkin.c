#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int childAction() {
  printf("Child PID: %d\n", getpid());
  srand(getpid());
  int random = (rand() % 16) + 5;
  printf("Child %d sleeping for %d seconds...\n", getpid(), random);
  sleep(random);
  printf("Child %d finished!\n", getpid());
  return random;
}

int main() {
  printf("Pre-forking message...\n\n");

  int child = fork();
  if (!child) {  // child process
    return childAction();
  }
  else { // parent process
    child = fork();
    if (!child) {  // child process
      return childAction();
    }

    int status;
    int finishedchild = wait(&status);
    printf("Child %d finished first! Slept for %d seconds.\n", finishedchild, WEXITSTATUS(status));
    printf("\nParent %d finished!\n", getpid());
  }
  return 0;
}