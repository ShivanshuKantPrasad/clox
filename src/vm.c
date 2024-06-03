#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "vm.h"
#include "debug.h"
#include "memory.h"

VM vm;

static void resetStack() {
  if (vm.stack == NULL) vm.stack = (Stack *)malloc(sizeof(Stack));
  vm.stack->values = NULL;
  vm.stack->count = 0;
  vm.stack->capacity = 0;
}

void initVM() {
  resetStack();
}

void freeVM() {

}

void push(Value value){
  if (vm.stack->capacity < vm.stack->count + 1) {
    size_t oldCapacity = vm.stack->capacity;
    vm.stack->capacity = GROW_CAPACITY(oldCapacity);
    vm.stack->values = GROW_ARRAY(Value, vm.stack->values,
                               oldCapacity, vm.stack->capacity);
  }
  vm.stack->values [vm.stack->count] = value;
  vm.stack->count++;
}

Value pop(){
  vm.stack->count--;
  return vm.stack->values[vm.stack->count];
}

static InterpretResult  run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define READ_LONG_CONSTANT() (vm.chunk->constants.values[(READ_BYTE() << 16) + (READ_BYTE() << 8) + (READ_BYTE())])
#define BINARY_OP(op) \
  do {                      \
    double b = pop();       \
    double a = pop();       \
    push(a op b);           \
  } while(false)

  for(;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("         ");
    for(int index = vm.stack->count - 1; index >= 0; index--) {
      printf("[ ");
      printValue(vm.stack->values[index]);
      printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
    uint8_t instruction;
    switch(instruction = READ_BYTE()) {
      case OP_CONSTANT: {
        Value constant = READ_CONSTANT();
        push(constant);
//        printValue(constant);
//        printf("\n");
        break;
      }
      case OP_ADD: BINARY_OP(+); break;
      case OP_SUBTRACT: BINARY_OP(-); break;
      case OP_MULTIPLY: BINARY_OP(*); break;
      case OP_DIVIDE: BINARY_OP(/); break;
      case OP_NEGATE: push(-pop()); break;
      case OP_CONSTANT_LONG: {
        Value constant = READ_LONG_CONSTANT();
        push(constant);
//        printValue(constant);
//        printf("\n");
        break;
      }
      case OP_RETURN: {
        printValue(pop());
        printf("\n");
        return INTERPRET_OK;
      }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
#undef READ_LONG_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(Chunk *chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}
