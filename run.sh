#!/bin/sh
rm output/*
gcc test.c -lm && ./a.out "$1" && feh output/*
