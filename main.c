#include "chunk.h"
#include <stdio.h>

int main() {
  printf("Hello World");
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, OP_RETURN);
  freeChunk(&chunk);
  return 0;
}
