#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
  bool calc;
  double r;
} Node;

/**
 * Cacher les calculs precedants pour optimiser.
**/
Node CACHE[100];
double recurse_suite(uint32_t a);
double direct_suite(uint32_t a);

// Asumer que les arguments sont valide:
// arg 1 = a. : un entier.
// compiler avec gcc -O3 -lm
int main(int argc, char** argv) {
  //Scanner les arguments.  
  int a;
  sscanf(argv[1], "%d", &a);
  // Vérifuer resolution:
  printf("a(%d) = %.4e\n", a, direct_suite(a));
  //Netoyer le cache.
  for (int i = 0; i < 100; i++) {
    CACHE[i].calc = false;
    CACHE[i].r = 0.0;
  }

  // Definition des valeurs de depart
  const double CONST_POW[] = {-1, 28, -240, 1948, -16080};
  for (int i = 0; i < 5; i++) {
    CACHE[i].calc = true;
    CACHE[i].r = CONST_POW[i];
  }

  struct timespec start, end;
  double time_spent;
  clock_gettime(CLOCK_REALTIME, &start);
  double res = recurse_suite(a);
  clock_gettime(CLOCK_REALTIME, &end);
  time_spent = (end.tv_sec - start.tv_sec)*1e6 + (end.tv_nsec - start.tv_nsec)*1e-3;
  printf("Result: %.4e\n", res);
  printf("Time spent: %f µs\n", time_spent);
  return 0;
}

// Definition de la fonction recursive
const double CONST_FACT[] = {-25, -233, -995, -1866, -1080};
double recurse_suite(uint32_t a) {
  if (CACHE[a].calc) return CACHE[a].r;
  else {
    double n[5];
    double result = 0.0;
    for (int i = 0; i < 5; i++) {
      if (CACHE[a-i-1].calc)
        n[i] = CACHE[a-i-1].r;
      else
        n[i] = recurse_suite(a-i-1);
      n[i] *= CONST_FACT[i];
      result += n[i];
    }
    CACHE[a].calc = true;
    CACHE[a].r = result;
    return result;
  }
}

double direct_suite(uint32_t a) {
  return (-740/149.0)*pow(-1, a) +
    (-7814/149.0)*pow(-4, a) + 
    (1063/149.0)*pow(-5, a) +
    (-4106/149.0)*pow(-6, a) +
    (-120/149.0) *pow(-9, a);
}