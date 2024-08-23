#!/bin/bash

script_dir=$(dirname "$0")

for file in $(find "$script_dir" -type f); do
    echo $file
    if [[ "$file" == *.c ]]; then
        filename=$(basename "$file" .c)
        compiled_filename="$filename"

        gcc "$file" -o "$compiled_filename" -Wall -Wextra -Werror -lm
        echo "Compiled $file to $compiled_filename"

        echo src/"$compiled_filename" >> ../.gitignore
    fi
done
