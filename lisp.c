
#include <stdio.h>
#include <stdlib.h>

void repl(void)
{
    int ret, c, count;

    while (1) {
        fputs("> ", stdout);
        count = 0;
        while (1) {
            ret = fgetc(stdin);
            if (ret == EOF) {
                puts("");
                puts("BYE");
                return;
            }
            c = ret;
            if (c == '(') {
                count++;
            }
            if (c == ')') {
                count--;
            }
            if (c == '\n') {
                if (count == 0) {
                    puts("GOOD");
                }
                if (count != 0) {
                    puts("BAD");
                }
                break;
            }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        repl();
    }

    return 0;
}

