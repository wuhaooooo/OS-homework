#include "scheduler.h"
#include <stdio.h>
#include <fcntl.h>


void print_nth_prime(void * pn) {
  int n = *(int *) pn;
  int c = 1, i = 1;
  while(c <= n) {
    ++i;
    int j, isprime = 1;
    for(j = 2; j < i; ++j) {
      if(i % j == 0) {
        isprime = 0;
        break;
      }
    }
    if(isprime) {
      ++c;
    }
    yield();
  }
  printf("%dth prime: %d\n", n, i);
 
}

void read_file(){
  int fd = open("test.txt", O_RDONLY);
  if(fd == -1){
    printf("file open error!\n");
    return;
  }
  int buffer_size = 4;
  char buffer[buffer_size];
  while(read_wrap(fd, buffer, buffer_size) != 0){
    printf("%s\n", buffer);
  }
  printf("file read finished!\n");
}

void read_IO(){
  int buffer_size = 4;
  char buffer[buffer_size];
  printf("Input something!\n");
  read_wrap(0, buffer, buffer_size);
  printf("Here is the input: %s\n", buffer);
}

int main(void) {
  scheduler_begin();

  thread_fork(read_IO, NULL);
  thread_fork(read_file, NULL);
  int a = 100;
  thread_fork(print_nth_prime, &a);
  scheduler_end();
}
