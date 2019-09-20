#!/bin/bash

# collect c source file
for e in $(ls *.c 2>/dev/null); do
    srcs="$srcs ${e%.c}"
done

# collect cc source file
for e in $(ls *.cc 2>/dev/null); do
    srcs="$srcs ${e%.cc}"
done

srcs="srcs = $srcs"
rm -rf .premake

echo $srcs > .premake
cat Makefile | tail -n +2 >> .premake && mv .premake Makefile
