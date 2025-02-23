#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int w, h; // width, height
} Plane;

typedef struct {
    Plane base;
    int d; // depth
} Volume;

// O tamanho da union é determinado pelo maior dos seus membros. O maior campo é char c[10], então a union deveria ter pelo menos 10 bytes.Os ints geralmente precisam de estar alinhados em endereços múltiplos de 4 bytes.

// Se Mix tivesse apenas 10 bytes, o Plane p(que contém ints) ficaria mal alinhado na memória, o que poderia gerar problemas de performance.

// Como é que o compilador resolve isso ?

// Adiciona 2 bytes de padding após c[10] para garantir que Plane p esteja corretamente alinhado.Assim, Mix fica com 12 bytes para manter os acessos à memória eficientes.
typedef union {
  int i;      // 4 bytes
  char c[10]; // 10 bytes
  Plane p;    // 8 bytes
} Mix;

void print_plane(Plane *p) {
    printf("W %d, H %d\n", p->w, p->h);
}
void print_volume(Volume *v) {
    printf("W %d, H %d, D %d\n", v->base.w, v->base.h, v->d);
}

Plane *new_plane(int w, int h) {
  Plane *p = malloc(sizeof(Plane));
  p->w = w;
  p->h = h;
  return p;
}
Volume *new_volume(Plane *p, int d) {
  Volume *v = malloc(sizeof(Volume));
  v->base.w = p->w;
  v->base.h = p->h;
  v->d = d;
  return v;
}

int main() {
    Plane p = {5, 2};
    Volume v = {p, 3};
    print_plane(&p);    // É preciso passar por referência? Sim
    print_plane((Plane *) &v);  // ??É um cast
    print_volume(&v);

    printf("sizeof(Mix)=%u\n", sizeof(Mix));
    Mix m;
    m.p.h = 3;
    m.p.w = 5;
    printf("m.i=%d\n", m.i);
    print_plane(&m.p);
    strcpy(m.c, "Hello!\n");
    printf("%s", m.c); // %s - format for a string
    return 0;
}