#!/bin/sh

cc -std=c99 -pedantic -Wall -Wextra consume.c -o consume -lxcb -lxcb-util -lxcb-ewmh
