#!/bin/sh

LIB_PATH=$(pwd)
export LD_LIBRARY_PATH=$LIB_PATH
rustc --crate-type cdylib ./rust/src/helper.rs
gcc main.c -o main -L. -lhelper -lraylib -lm
