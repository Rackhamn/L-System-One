#!/bin/sh
[ -d "output" ] || mkdir -p "output"
gcc test.c -lm && ./a.out "$1" && feh output/*
