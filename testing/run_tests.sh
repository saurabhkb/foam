#!/bin/bash

num=1
for i in $(ls tests/in*); do 
	./simulator $i | diff - ${i/in/out} 1> /dev/null
	ret=$?
	if [ $ret -eq 0 ]
	then
		echo Test $num : Pass
	else
		echo Test $num : Fail
	fi
	((num++))
done
