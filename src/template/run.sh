#!bin/bash
if ! g++ -std=gnu++2a -Wall -Wextra -Wshadow -DGLIBCXX_DEBUG -DLOCAL -ftrapv $1.cpp; then
    echo CE
    return
fi

for f in samples-$1/*.in
do
    if ! ./a.out < $f > temp; then
        echo RE on $f
        continue
    fi
    if ! diff ${f/in/ans} temp; then
        echo WA on $f
        continue
    fi
    echo passed $f
done