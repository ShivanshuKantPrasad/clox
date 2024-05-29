#pragma once

#include "common.h"

typedef enum {
  OP_RETURN,
} OpCode;

typedef struct {
  uint8_t *code;
  size_t count;
  size_t capacity;
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte);
