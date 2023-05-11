#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

#include "suite.c"

// Asumer que les arguments sont valide:
// arg 1 = a. : un entier.
// compiler avec gcc -O3 -lm
int main(int argc, char** argv) {
  clean_cache();  
  //Scanner les arguments.  
  int a;
  sscanf(argv[1], "%d", &a);
  // Vérifuer resolution:
  // printf("a(%d) = %.4e\n", a, direct_suite(a));
  
  const int NB_TESTS = 1000000;
  double res;
  long double min_time = 10;
  for (int i = 0; i < NB_TESTS; ++i) {
    struct timespec start, end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    res = recurse_suite(a);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    double time_spent = (end.tv_sec - start.tv_sec)*1e6 + (end.tv_nsec - start.tv_nsec)*1e-3;
    if (time_spent < min_time) {
      min_time = time_spent;
    }
  }
  
  if (argc >= 3) {
    printf("%Lf\n", min_time);
  } else {
    printf("Result: %.4e\n", res);
    printf("Time spent: %Lf µs\n", min_time);
  }

  return 0;
}
