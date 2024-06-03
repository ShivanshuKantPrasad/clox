#pragma once

#include "chunk.h"
#include "value.h"

#define STACK_INIT 256

typedef struct {
  Value *values;
  size_t count;
  size_t capacity;
} Stack;

typedef struct {
  Chunk *chunk;
  uint8_t *ip;
  Stack *stack;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk *chunk);
void push(Value value);
Value pop();