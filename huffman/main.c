#include "element.h"
#include "huffman.h"

#include <stdint.h>
#include <stdio.h>

int main() {
  element A = {'A', 1.0 / 18};
  element B = {'B', 2.0 / 18};
  element C = {'C', 3.0 / 18};
  element D = {'D', 4.0 / 18};
  element E = {'E', 8.0 / 18};

  element *ele[] = {&A, &B, &C, &D, &E, NULL};
  huffman(ele, 5);
  for (int i = 0; i < 5; i++) {
    char c[10];
    c[ele[i]->length] = '\0';

    // convert to binary charaters to print
    for (int j = 0; j < ele[i]->length; j++) {
      c[ele[i]->length - j - 1] = ((ele[i]->coded >> j) & 1) + 48;
    }
    printf("%c: %s\n", ele[i]->e, c);
  }

  char str[] = "ADEEADEYCCCEEDABEEDEEB";

  uint8_t stream[OUTPUT_BYTES];
  int bits = encoder(str, ele, stream);
  printf("%d\n", bits);

  return 0;
}
