#include "chunk.h"
#include "memory.h"

#include <stdint.h>

void initChunk(Chunk *chunk) {
  chunk->code = NULL;
  initValueArray(&chunk->constants);
  initLine(&chunk->lines);
  chunk->count = 0;
  chunk->capacity = 0;
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  freeValueArray(&chunk->constants);
  freeLine(&chunk->lines);
  initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    size_t oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code =
        GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
  }

  writeLine(&chunk->lines, line);
  chunk->code[chunk->count] = byte;
  chunk->count++;
}

size_t addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

void writeConstant(Chunk *chunk, Value value, int line) {
  size_t constant = addConstant(chunk, value);
  if (constant < 256) {
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, constant, line);
  } else {
    writeChunk(chunk, OP_CONSTANT_LONG, line);
    writeChunk(chunk, constant >> 16, line);
    writeChunk(chunk, constant >> 8, line);
    writeChunk(chunk, constant, line);
  }
}

void initLine(Line *lines) {
  lines->number = NULL;
  lines->length = NULL;
  lines->count = 0;
  lines->capacity = 0;
}

void freeLine(Line *lines) {
  FREE_ARRAY(int, lines->length, lines->capacity);
  FREE_ARRAY(int, lines->number, lines->capacity);
  initLine(lines);
}

void writeLine(Line *lines, int line) {
  if (lines->count > 0 && lines->number[lines->count - 1] == line) {
    lines->length[lines->count - 1]++;
  } else {
    if (lines->capacity < lines->count + 1) {
      size_t oldCapacity = lines->capacity;
      lines->capacity = GROW_CAPACITY(oldCapacity);
      lines->length =
          GROW_ARRAY(int, lines->length, oldCapacity, lines->capacity);
      lines->number =
          GROW_ARRAY(int, lines->number, oldCapacity, lines->capacity);
    }
    lines->number[lines->count] = line;
    lines->length[lines->count] = 1;
    lines->count++;
  }
}

int getLine(Line *lines, int offset) {
  int index = 0;
  while (offset > lines->length[index]) {
    offset -= lines->length[index];
    index++;
  }
  return lines->number[index];
}
