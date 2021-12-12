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

if [[ $1 == tree ]]
then
    clang++ -Wall -Wextra -Werror -std=c++98 srcs/test_tree.cpp -o test_tree && ./test_tree
    rm -f test_tree
fi

rm -f ft.txt std.txt