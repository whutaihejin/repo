#!/bin/bash
[ -d "build" ] || mkdir build
cd build && cmake .. && make VERBOSE=1 install && cd ..
