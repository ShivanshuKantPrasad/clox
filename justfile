main:
  gcc main.c chunk.c memory.c -o build/main

run: main
  ./build/main
