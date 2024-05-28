#! /bin/env bash


gcc -o lissajous lissajous.c -I./raylib/src -L./raylib/src -lraylib -lm -ldl -lpthread

