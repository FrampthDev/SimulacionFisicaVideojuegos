#!/bin/bash

src_dir="./src/"

name="Game"

libraries=(-lraylib)

sources=() 

while IFS= read -r -d $'\0'; do
    sources+="$REPLY "
done < <(find $src_dir -name "*.cpp" -print0)

echo "Compiling:"
for file in $sources; do
    echo "$file"
done

g++ $sources $libraries -o "./bin/$name"

if [[ $1 == "run" ]]; then
    ./bin/$name
fi
