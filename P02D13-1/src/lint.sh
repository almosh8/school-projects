if [[ "$1" != "" ]]; then
clang-format -n $1
else
clang-format -n *.c
fi
