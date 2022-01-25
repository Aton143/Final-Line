#!/bin/sh
echo "Building project"
RAYLIB_CONFIG=`pkg-config --libs --cflags raylib`
SOURCE_NAME="$1"
EXE_NAME="$2"

rm ../*.editor

clang -O2 ${SOURCE_NAME:-Editor}.c Buffer.c ${RAYLIB_CONFIG} -o ../${EXE_NAME:-example}.editor

echo "Name of Executable: ${EXE_NAME:-example}.editor"
