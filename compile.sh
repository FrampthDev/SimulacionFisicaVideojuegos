#!/bin/bash

src_dir="./src/"

name="Game"

libraries=(-lraylib)

sources=() 

#while IFS= read -r -d $'\0'; do
#    sources+="$REPLY "
#done < <(find $src_dir -name "*.cpp" -print0)

while IFS= read -r -d $'\0'; do
    sources+="$REPLY "
done < <(find $src_dir -name "*.c" -print0)


echo "Compiling files:"
for file in $sources; do
    echo "$file"
done

gcc $sources $libraries -o "./bin/$name" -g -lm

if [[ $1 == "run" ]]; then
    ./bin/$name
fi
