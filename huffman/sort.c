#include "sort.h"

void sortLastNode(element *nodes[], int n) {
  int compareIdx = n-1;
  while (compareIdx > 0 &&
         nodes[compareIdx - 1]->prob < nodes[compareIdx]->prob) {
    element *tmp = nodes[compareIdx - 1];
    nodes[compareIdx - 1] = nodes[compareIdx];
    nodes[compareIdx] = tmp;
    --compareIdx;
  }
}

// TODO bubble sort here, maybe it can be optimized
// by other sort algorithm
void sortNodes(element *nodes[], int n) {
  for (int i = 1; i < n; i++)
    sortLastNode(nodes, i+1);
}
