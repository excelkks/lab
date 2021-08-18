#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "element.h"
#include <stdint.h>

element *buildSymbolTree(element *ele[], int n);
void codeSymbol(element *root);
void releaseSymbolTree(element *root);
void huffman(element *ele[], int n);
int encoder(const char str[], element *ele[], uint8_t *stream);

#endif
