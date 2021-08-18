#ifndef ELEMENT_H
#define ELEMENT_H

#define OUTPUT_BYTES 8
#define OUTPUT_BITS (OUTPUT_BYTES * 8)

typedef struct element {
  char e;      // element
  double prob; // probality
  int coded;
  unsigned length; // length of coded binary bit;
  struct element *left;
  struct element *right;
} element;

#endif
