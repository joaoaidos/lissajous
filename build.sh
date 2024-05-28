#! /bin/env bash

if [ ! -f ./raylib/src/libraylib.a ]; then
  make -C ./raylib/src/
fi

gcc -o lissajous lissajous.c -I./raylib/src -L./raylib/src -lraylib -lm -ldl -lpthread

