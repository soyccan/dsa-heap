#!/bin/sh
g++ -O2 -std=c++14 -o wa wa.cpp
g++ -O2 -std=c++14 -o ac ac.cpp
gcc -O2 -o rand rand.c
while true; do
    printf .
    ./rand >in
    ./ac <in >out || break
    ./wa <in >tmp || break
    diff out tmp || break
done
