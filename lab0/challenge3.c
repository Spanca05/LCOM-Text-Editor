#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int w, h; // width, height
} Plane;

Plane *create_plane() {
  //Plane plane = {1, 2}; // Variável local
  //return &plane;  // Retorna o endereço de uma variável local
  // Quando a função termina, a memória de plane é libertada. Retornar o enderço de uma variável local significa que plane->w pode conter lixo de memória ou causar um segmentation fault error.
  Plane *plane = malloc(sizeof(Plane));
  plane->w = 1;
  plane->h = 2;
  return plane;
}
int main() {
  Plane *plane = create_plane();
  printf("Width is %d\n", plane->w);
  return 0;
}