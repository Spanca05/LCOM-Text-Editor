#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int w, h; // width, height
} Plane;

typedef struct {
  Plane base; // Plane está contido no Volume
  int d;      // depth
} Volume;



void print_plane(Plane *p) {
  printf("W %d, H %d\n", p->w, p->h);
}

void print_volume(Volume *v) {
  printf("W %d, H %d, D %d\n", v->base.w, v->base.h, v->d);
}

int main() {
  // Criar um ponteiro para Plane dinamicamente
  Plane *p = (Plane *) malloc(sizeof(Plane));
  p->w = 5;
  p->h = 2;

  // Criar um ponteiro para Volume dinamicamente
  Volume *v = (Volume *) malloc(sizeof(Volume));
  v->base.w = 4;
  v->base.h = 3;
  v->d = 7;

  // Usar as funções de print
  printf("Printing Plane:\n");
  print_plane(p);

  printf("Printing Volume:\n");
  print_volume(v);

  printf("Printing Volume as Plane (cast):\n");
  print_plane((Plane *) v); // Cast para Plane*

  // Libertar memória antes de terminar
  free(p);
  free(v);



  return 0;
}
