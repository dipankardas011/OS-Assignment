#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main(int argc, char *argv[]) {
  int k, n = 3, id;
  double x = 0, z, d = 1.0;

  id = 0;
  for (k = 0; k < n; k++) {
    id = fork();
    if (id < 0) {
      //printf(1, "%d failed in fork!\n", getpid());
      exit();
    }
    if (id > 0) {
      //printf(1, "Parent %d creating child %d\n",getpid(), id);
      wait();
    } else {
      //printf(1, "Child %d created\n",getpid());

      for (z = 0; z < 80000000.00; z += d)
        x = x + 3.14 * 89.64;  // useless calculation
      break;
    }
  }
  
  exit();
}
