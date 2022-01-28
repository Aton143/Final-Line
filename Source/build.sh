#!/bin/sh
echo "Building project"
RAYLIB_CONFIG=`pkg-config --libs --cflags raylib`
COMPILE_FILES=`find . * | grep "^[A-Z].*\.c$"`
echo $COMPILE_FILES
EXE_NAME="$1"

rm ../*.editor

gcc -O2 ${COMPILE_FILES:-Editor.c Buffer.c Render.c} ${RAYLIB_CONFIG} -o ../${EXE_NAME:-example}.editor

echo "Name of Executable: ${EXE_NAME:-example}.editor"
