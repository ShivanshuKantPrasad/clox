#pragma once

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT_LONG,
  OP_CONSTANT,
  OP_NIL,
  OP_TRUE,
  OP_FALSE,
  OP_POP,
  OP_GET_LOCAL,
  OP_GET_GLOBAL,
  OP_DEFINE_GLOBAL,
  OP_SET_LOCAL,
  OP_SET_GLOBAL,
  OP_GET_UPVALUE,
  OP_SET_UPVALUE,
  OP_EQUAL,
  OP_GREATER,
  OP_LESS,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NOT,
  OP_NEGATE,
  OP_PRINT,
  OP_JUMP,
  OP_JUMP_IF_FALSE,
  OP_LOOP,
  OP_CALL,
  OP_CLOSURE,
  OP_CLOSE_UPVALUE,
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
void writeConstant(Chunk *chunk, Value value, int line);

void initLine(Line *lines);
void freeLine(Line *lines);
void writeLine(Line *lines, int line);
int getLine(Line *lines, int offset);
