#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void sievePrime(int *pl);


int
main(int argc, char *argv[])
{
  
  int pl[2];
  pipe(pl);
  
  if(fork() == 0) {     // child process
    close(pl[1]);
    sievePrime(pl);

  } else {      // parent process
    close(pl[0]);
    for (int i = 2; i < 36; i++) {
        write(pl[1], &i, sizeof(int));
    }       
    close(pl[1]);
    wait(0);                                              
  }
  exit(0);
}


void sievePrime(int *pl) {
    int n;  
    int currentPrime;
    // printf("%d, %d \n", pl[0], pl[1]);
    if (read(pl[0], &n, sizeof(int)) == 0) {
        exit(0);
    }
    currentPrime = n;
    printf("prime %d \n", n);  // print the first prime 2
    int pr[2];
    pipe(pr);
    if (fork() == 0) {  // grandchild process
        close(pl[0]);
        close(pr[1]);
        sievePrime(pr);
    } else {    // child process
        close(pr[0]);
        while (read(pl[0], &n, sizeof(int))) {
            if (n % currentPrime != 0) {
                write(pr[1], &n, sizeof(int));

            }
        }
        close(pr[1]);
        wait(0);
    }
}