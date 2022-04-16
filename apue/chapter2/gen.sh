#!/bin/bash

echo "int main() {"
for entry in $(cat sysconf.conf); do
    # echo $entry
    echo "#ifdef $entry"
    echo "    printf(\"$entry defined to be %ld\n\", (long)$entry+0);"
    echo "#else"
    echo "    printf(\"no symbol for $entry\n\");"
    echo "#endif"
    # sysconf
    echo "#ifdef _SC_$entry"
    echo "    pr_sysconf(\"$entry = \", _SC_$entry);"
    echo "#else"
    echo "    printf(\"no symbol for _SC_$entry\n\");"
    echo "#endif"
    echo "printf(\"\n\");"
done
echo "    return 0;"
echo "}"
