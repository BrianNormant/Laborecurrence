#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "suite.c"


// Asumer que les arguments sont valide:
// arg 1 = a. : un entier.
// compiler avec gcc -O3 -lm
int main(int argc, char* argv[]) {
  clean_cache();  
  //Scanner les arguments.  
  int a;
  sscanf(argv[1], "%d", &a);
  // Vérifuer resolution:
  printf("a(%d) = %.4e\n", a, direct_suite(a));

  clock_t start, end;
  double time_spent;
  start = clock();
  double res = recurse_suite(a);
  end = clock();
  time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Result: %.4e\n", res);
  printf("Time spent: %f µs\n", time_spent*1000000);
  return 0;
}
