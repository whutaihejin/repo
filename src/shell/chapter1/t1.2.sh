#!/bin/bash

echo "cannot!"
echo "Welcome to Bash"
echo Welcome to Bash
echo 'text in quotes'
echo "cannot include exclamation -! within double quotes"
echo Hello world!
echo 'Hello world!'
echo "Hello world\!"
echo -n "ll";echo "xx"

# print
printf "Hello world"
printf " Hello world\n"

# format substitution character
printf "%-5s %-10s %-4s\n" No Name Mark
printf "%-5s %-10s %-4.2f\n" 1 Saratch 80.3456
printf "%-5s %-10s %-4.2f\n" 2 James 90.9989 
printf "%-5s %-10s %-4.2f\n" 3 Jeff 77.564

echo -e "1\t2\t3"
echo -e "\e[1;31m This is red text \e[0m"
echo -e "\e[1;42m Green background \e[0m"
