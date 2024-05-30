cmake_minimum_required(VERSION 3.10)
project(clox)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main src/chunk.c src/chunk.h src/common.h src/debug.c src/debug.h src/main.c src/memory.c src/memory.h
        src/value.h
        src/value.c)
