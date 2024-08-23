script_dir=$(dirname "$0")

for file in $(find "$script_dir" -type f); do
    if [[ "$file" == *.c || "$file" == *.h]]; then
        clang-format -i $file

        echo "Formatted code at $file"
    fi
done

git add .
git commit -m "automated commit"
git push
