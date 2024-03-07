#!/bin/sh

export LD_LIBRARY_PATH=./rust/src/
rustc --crate-type cdylib ./rust/src/helper.rs
gcc main.c -o main -L. -lhelper -lraylib
