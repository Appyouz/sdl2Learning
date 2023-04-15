#!/bin/bash

COMPILER="g++"
ARGS="-g -std=c++17"
SRC="./src/*.cpp"
INCLUDE="./include"
BINARY="./bin/main"
LIBS="-lSDL2 -lSDL2_ttf -lSDL2_mixer -ldl"

echo "Compiling on ${OSTYPE}"

# Build the compile string
# if [["$OSTYPE" == "linux-gnu"* ]]; then
    # echo ""
# fi

COMPILE="${COMPILER} ${ARGS} ${SRC} -I ${INCLUDE} -o ${BINARY} ${LIBS}"

echo ${COMPILE}

eval $COMPILE
