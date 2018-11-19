#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

void check_error() {
  if (errno) {
    printf("Error #%d: %s\n",errno,strerror(errno));
    exit(1);
  }
}

int random_num() {
  int * num = malloc(4);
  int random_dest = open("/dev/urandom",O_RDONLY);
  check_error();
  read(random_dest,num,4);
  int output = *num;
  free(num);
  if (output < 0) {
    output = -1 * output;
  }
  return output;
}

int main() {
  printf("I am the parent and my pid is %d.\n",getpid());
  int f1 = fork();
  int f2 = -1;
  if (f1){
    f2 = fork();
  }
  check_error();
  //Parent
  if (f1 && f2) {
    printf("Successful fork\n");
    int status = 0;
    wait(&status);
    printf("Child with pid %d has finished sleeping for %d seconds.\n",f1,WEXITSTATUS(status));
  }
  //Child
  else {
    printf("I am a child and my pid is %d\n",getpid());
    int random_sleep_2 = (random_num() % 16) + 5;
    sleep(random_sleep_2);
    printf("I am child %d and I am done sleeping.\n",getpid());
    return random_sleep_2;
  }
  printf("Parent is done with its work.\n");
  return 0;
}
