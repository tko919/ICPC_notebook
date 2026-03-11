#!bin/bash
for i in {A..K}
do
    unzip ~/Donwloads/samples-$i.zip -d $i
    touch $i.cpp
done