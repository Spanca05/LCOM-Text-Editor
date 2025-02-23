#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT 100
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

void process_command(char * input) {
    char cmd[MAX_INPUT];
    unsigned int a, b;

    if(sscanf(input, "%s %u %u", cmd, &a, &b) < 2) {
        printf("Invalid Input\n");
        return;
    }

    if(strcmp(cmd, "and") == 0) {
        printf("%u\n", a & b);
    }

    else if(strcmp(cmd, "or") == 0) {
        printf("%u\n", a | b);
    }

    else if(strcmp(cmd, "set") == 0) {
        printf("%u\n", a | BIT(b));
    }

    else if(strcmp(cmd, "unset") == 0) {
        printf("%u\n", a & ~BIT(b));
    }

    else if(strcmp(cmd, "byte") == 0) {
        printf("%u\n", (a >> (b * 8)) & 0xFF);  // Como queremos o byte na posição b, multiplicamos b por 8 bits, dando o número de right shifts que teremos que dar, e depois, para extrair o byte fazemos & 0xFF = 0b11111111, extraindo assim o byte.
    }

    else if(strcmp(cmd, "print") == 0) {
        print_bits(a);
    }

    else {
      printf("Unknown Command: %s\n", cmd);
    }
}

int main() {
    process_command("and 3 5");      // Esperado: 1
    process_command("or 3 5");       // Esperado: 7
    process_command("set 4 1");      // Esperado: 6
    process_command("unset 6 1");    // Esperado: 4
    process_command("byte 65534 1"); // Esperado: 255
    process_command("print 7");      // (Se `print` estiver implementado, imprime os bits de 7)
    process_command("invalido 10");  // Esperado: "Comando desconhecido"
    return 0;
}