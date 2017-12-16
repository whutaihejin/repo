#!/bin/bash

# cat /proc/$PID/environ
# pgrep hotspot
# cat /proc/12501/environ | tr '\0' '\n'

var="value"
echo $var
echo ${var}
echo '$var will print $var'
echo ${#var}
echo $SHELL
echo $0
if [ $UID -ne 0 ]; then
    echo Non root user. Please run as root.
else
    echo Root user
fi

fruit=apple
count=5
echo "We have $count ${fruit}(s)"

HTTP_PROXY=192.169.1.23:3128
export HTTP_PROXY

echo $PATH

export PATH="$PATH:/home/taihejin/bin"
PATH="$PATH:/home/taihejin/bin"
export PATH
echo $PATH

