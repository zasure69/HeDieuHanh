#!/bin/sh
foo=1
while [ "$foo" -le 16 ]
do
    echo "Here $foo"
    foo=$(($foo+1))
done
exit 0