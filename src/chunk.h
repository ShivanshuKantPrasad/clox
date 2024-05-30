#pragma once

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_RETURN,
} OpCode;

typedef struct {
  int *number;
  int *length;
  size_t count;
  size_t capacity;
} Line;

typedef struct {
  uint8_t *code;
  Line lines;
  ValueArray constants;
  size_t count;
  size_t capacity;
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
size_t addConstant(Chunk *chunk, Value value);

void initLine(Line *lines);
void freeLine(Line *lines);
void writeLine(Line *lines, int line);
int getLine(Line *lines, int offset);
