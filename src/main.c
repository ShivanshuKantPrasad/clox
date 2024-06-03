#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main() {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

//  for(int i = 0; i < 500; i++) {
//    writeConstant(&chunk, 1.0f + i / 10.0f, i / 3);
//  }
  writeConstant(&chunk, 1.2, 123);
  writeConstant(&chunk, 3.4, 123);
  writeChunk(&chunk, OP_ADD, 123);
  writeConstant(&chunk, 5.6, 123);
  writeChunk(&chunk, OP_DIVIDE, 123);
  writeChunk(&chunk, OP_NEGATE, 123);
  writeChunk(&chunk, OP_RETURN, 126);

//  disassembleChunk(&chunk, "test chunk");
  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
  return 0;
}
