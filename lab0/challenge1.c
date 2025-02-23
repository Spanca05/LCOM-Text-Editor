#include <stdio.h>
#include <stdlib.h>
#define BIT(n) (1 << (n)) // () prevent precedence issues

void print_bits(int num) {
  int num_bits = sizeof(int) * 8; // number of bits in an int
  for (int i = num_bits - 1; i >= 0; i--) {
    if (num & BIT(i))
      printf("%d", 1); // Verifica se o bit na posição i é 1, se for, dá print a 1, senão dá print a 0
    else
      printf("%d", 0);
  }
  printf("\n");
}

int main() {
  print_bits(8);
  print_bits(12);
  return 0;
}