#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sysinfoapi.h>
#include <stdbool.h>
#include <math.h>

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

  long long int start, end;
  double time_spent;
  start = GetTickCount64();
  double res = recurse_suite(a);
  end = GetTickCount64();
  time_spent = (end-start) * 1e3;
  printf("Result: %.4e\n", res);
  printf("Time spent: %f µs\n", time_spent);
  return 0;
}
