#include <stdio.h>
#include <sys/resource.h>

int main() {
  struct rlimit rlim;
  getrlimit(RLIMIT_STACK, &rlim);
  printf("stack size: %ld\n", (long)rlim.rlim_cur);
  getrlimit(RLIMIT_NPROC, &rlim);
  printf("process limit: %ld\n", (long)rlim.rlim_cur);
  getrlimit(RLIMIT_NOFILE, &rlim);
  printf("max file descriptors: %ld\n", (long)rlim.rlim_cur);
  return 0;
}
