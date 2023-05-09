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
  printf("a(%d) = %.4e\n", a, direct_suite(a));
  
  const int NB_TESTS = 1;
  double res;
  long double time_spent = 0.0;
  for (int i = 0; i < NB_TESTS; ++i) {
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    res = recurse_suite(a);
    clock_gettime(CLOCK_REALTIME, &end);
    time_spent += (end.tv_sec - start.tv_sec)*1e6 + (end.tv_nsec - start.tv_nsec)*1e-3;
  }
  time_spent = time_spent / NB_TESTS;
  
  printf("Result: %.4e\n", res);
  printf("Time spent: %Lf µs\n", time_spent);
  return 0;
}
