
clang -std=c99 -pedantic -Wall -Werror -fsanitize=address,undefined -o lisp lisp.c main.c

