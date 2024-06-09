#pragma once

#include "chunk.h"
#include "table.h"
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
  Table strings;
  Obj *objects;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret(const char *source);
void push(Value value);
Value pop();
