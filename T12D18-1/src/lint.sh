for file in $(find "$script_dir" -type f); do
    if [[ "$file" == *.c || "$file" == *.h ]]; then
        clang-format -n $file

        echo "Checking code style at $file"
    fi
done
