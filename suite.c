#include <math.h>
#include <stdbool.h>
#include <stdint.h>

// Definition de la fonction recursive

typedef struct {
  bool calc;
  double r;
} Node;

/**
 * Cacher les calculs precedants pour optimiser.
**/
Node CACHE[100];

void clean_cache() {
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
}

const double CONST_FACT[] = {-25, -233, -995, -1866, -1080};
double recurse_suite(uint32_t a) {
  if (CACHE[a].calc) return CACHE[a].r;
  else {
    double n;
    double result = 0.0;
    for (int i = 0; i < 5; i++) {
      if (CACHE[a-i-1].calc)
        n = CACHE[a-i-1].r;
      else
        n = recurse_suite(a-i-1);
      n *= CONST_FACT[i];
      result += n;
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
