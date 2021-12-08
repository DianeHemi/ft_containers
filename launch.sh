#!/bin/bash

./test_ft > ft.txt
./test_std > std.txt

DIFF=$(diff -c ft.txt std.txt)

echo
echo "Checking differences : "

if [ "$DIFF" == "" ]
then
    echo "No differences" ${GREEN}✅
else
    echo "A problem was found" ${RED}❌
fi

if [[ $1 == show ]]
then
    diff -y ft.txt std.txt
fi

rm -f ft.txt std.txt