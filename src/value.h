#pragma once

#include "common.h"

typedef double Value;

typedef struct {
  Value* values;
  size_t count;
  size_t capacity;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);