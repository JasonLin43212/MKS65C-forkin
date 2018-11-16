#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

void check_error() {
  if (!errno) {
    printf("Error #%d: %s",errno,strerror(errno));
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
  int f = fork();
  check_error();
  int f1_sleep = waitpid(f,WEXITSTATUS,0);

  //Parent
  if (f) {
    printf("Successful fork");
    /*
    int f2 = fork();
    check_error();
    waitpid(2,WEXITSTATUS,0);

    
    //Parent
    if (f2) {
      
    }
    //Child
    else {
      printf("I am a child and my pid is %d",getpid());
      int random_sleep_2 = (random_num % 16) + 5;
      sleep(random_sleep_2);
      printf(
      return random_sleep_2;
    }
    */
  }
  //Child
  else {
    printf("I am a child and my pid is %d",getpid());
    int random_sleep = (random_num % 16) + 5;
    sleep(random_sleep);
    return random_sleep_2;
  }


  
  return 0;
}
