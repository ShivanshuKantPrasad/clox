#include "chunk.h"
#include "debug.h"

int main() {
  Chunk chunk;
  initChunk(&chunk);

//  size_t constant = addConstant(&chunk, 1.2);
//  writeChunk(&chunk, OP_CONSTANT, 123);
//  writeChunk(&chunk, constant, 123);
//  for(int i = 0; i < 500; i++) {
//    writeConstant(&chunk, 1.0f + i / 10.0f, i / 3);
//  }
  writeConstant(&chunk, 1.2, 123);
  writeConstant(&chunk, 1.3, 124);
  writeChunk(&chunk, OP_RETURN, 126);

  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  return 0;
}
