#include "huffman.h"
#include "element.h"
#include "sort.h"
#include <memory.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

element *buildSymbolTree(element *ele[], int n) {
  if (0 == n)
    return NULL;
  element *symbolTree = (element *)malloc(sizeof(element));
  symbolTree->coded = 0;
  symbolTree->length = 0;
  if (1 == n) {
    symbolTree->left = ele[0];
    symbolTree->right = NULL;
    symbolTree->prob = ele[0]->prob;
  } else {

    // numbers of node, include created nodes and Symbol leaves
    int nodeNumber = n;
    element *sortedNodes[n];
    memcpy(sortedNodes, ele, sizeof(element *) * n);
    sortNodes(sortedNodes, nodeNumber);
    while (nodeNumber != 2) {
      element *node = (element *)malloc(sizeof(element));
      node->left = sortedNodes[nodeNumber - 2];
      node->right = sortedNodes[nodeNumber - 1];
      node->prob =
          sortedNodes[nodeNumber - 2]->prob + sortedNodes[nodeNumber - 1]->prob;
      sortedNodes[nodeNumber - 2] = node;

      // resort nodeNumber th element;
      nodeNumber--; // numbers of node remain
      sortLastNode(sortedNodes, nodeNumber);
    }
    symbolTree->left = sortedNodes[0];
    symbolTree->right = sortedNodes[1];
  }

  return symbolTree;
}

// code for all leaves
void codeSymbol(element *root) {
  element *left = root->left;
  element *right = root->right;
  if (left) {
    left->length = root->length + 1;
    left->coded = (root->coded << 1) + 1;
    codeSymbol(left);
  }
  if (right) {
    right->length = root->length + 1;
    right->coded = (root->coded << 1);
    codeSymbol(right);
  }
}

// release all node except leaves
void releaseSymbolTree(element *root) {
  element *left = root->left;
  element *right = root->right;
  if (left || right)
    free(root);
  else
    return;
  if (left)
    releaseSymbolTree(left);
  if (right)
    releaseSymbolTree(right);
}

void huffman(element *ele[], int n) {
  element *symbolTree = buildSymbolTree(ele, n);
  codeSymbol(symbolTree);
  releaseSymbolTree(symbolTree);
}

int encoder(const char str[], element *ele[], uint8_t *stream) {
  int bits = 0;
  int notInStream = 0;
  int idxStr = 0;
  char symbol = str[idxStr];
  uint32_t coded = 0;
  int idxWrite = 0;
  int i = 0;
  int eleNumber = 0;
  while (ele[i++])
    eleNumber++;
  while (symbol) {
    for (int j = 0; j < eleNumber; j++) {
      if (symbol == ele[j]->e) {
        coded = (coded << ele[j]->length) +
                (((1 << ele[j]->length) - 1) & ele[j]->coded);
        notInStream += ele[j]->length;
        break;
      }
    }
    // output 8 bits
    if (notInStream > 8) {
      stream[idxWrite++] = (uint8_t)((1 << 8) - 1) & coded;
      coded >>= 8;
      bits += 8;
    }

    symbol = str[++idxStr];
  }

  // less than or equal 8bits not in stream
  if (notInStream) {
    stream[idxWrite++] = (uint8_t)((1 << 8) - 1) & coded;
    bits += notInStream;
  }

  return bits;
}

void decoder(char *decoded, uint8_t *stream, int bits, element *ele[]) {
  int i = 0;
  int eleNumber = 0;
  while (ele[i++])
    eleNumber++;
  uint32_t reader;
  int idxReader = 0;
  int notRead = bits;
  int bitsInReader = 0;
  while (notRead > 8) {
    while (bitsInReader < 8) {
      reader = (reader << 8) + stream[idxReader++];
      bitsInReader += 8;
      notRead -= 8;
    }
  }
}
