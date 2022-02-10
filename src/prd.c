#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define STDOUT 1
#define STDIN 2

int main(int argc, char *argv[]) {
  printf(1, "PPID: %d\n", getppid());

// debuging purpose
  // printf(1, "ppid: %d\tpid: %d\n", getppid(), getpid());
  // int t = fork();
  // if (t == 0)
  // {
  //   printf(1, "Child process\n");
  //   printf(1, "Cppid: %d   pid: %d\n", getppid(), getpid());
  // }
  // else
  // {
  //   printf(1, "Parent process\n");
  //   printf(1, "Pppid: %d  pid: %d\n", getppid(), getpid());
  //   int t = wait();
  //   printf(1, "Child of pid: %d killed\n", t);
  // }

  exit();
}
