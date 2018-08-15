#!/bin/bash

function usage() {
  echo -e "uage:"
  echo -e " -h show this help message"
  echo -e " -g compile with the debug mode"
  echo -e " -c clean the cmake cache directory"
}

mode="release"
clean="false"

while getopts "hgcs" opt; do
    case "$opt" in
        g) mode="debug";;
        c) clean="true";;
        h) usage; exit;;
        ?) usage; exit;;
    esac
done

WORK_HOME="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$WORK_HOME"

# build dir
build_dir="${WORK_HOME}/cmake"
if [ "$clean" == "true" ]; then
  rm -rf "$build_dir"
fi
[ -d "$build_dir" ] || mkdir "$build_dir"

# compile the source to target
if [ "$mode" == "debug" ]; then
  cd $build_dir && cmake -DTARGET_DEBUG_MODE=ON .. && make VERBOSE=1 && make install 
else
  cd $build_dir && cmake -DTARGET_DEBUG_MODE=OFF .. && make && make install 
fi

if [ "$?" != "0" ]; then
  echo -e "leetcode build failed" && exit 2
fi
echo -e "leetcode build done" && exit 0
