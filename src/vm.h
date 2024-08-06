#pragma once

#include "object.h"
#include "table.h"
#include "value.h"
#include <stdint.h>

#define FRAMES_MAX 64
#define STACK_INIT 256

typedef struct {
  ObjClosure *closure;
  uint8_t *ip;
  int stack_pointer;
} CallFrame;

typedef struct {
  Value *values;
  size_t count;
  size_t capacity;
} Stack;

typedef struct {
  CallFrame frames[FRAMES_MAX];
  int frameCount;
  Stack *stack;
  Table globals;
  Table strings;
  ObjUpvalue *openUpvalues;
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
