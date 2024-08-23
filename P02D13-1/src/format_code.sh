 if [[ "$1" != "" ]]; then
clang-format -i $1
else
clang-format -i *.c
fi
