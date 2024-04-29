
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void repl(void)
{
    int ret, c, count, has_unmatched_close;

    while (1) {
        fputs("> ", stdout);
        count = 0;
        has_unmatched_close = 0;
        while (1) {
            ret = fgetc(stdin);
            if (ret == EOF) {
                puts("");
                puts("BYE");
                return;
            }
            c = ret;
            if (c == '(' && count < INT_MAX) {
                count++;
            }
            if (c == ')' && count > INT_MIN) {
                count--;
            }
            if (count < 0) {
                has_unmatched_close = 1;
            }
            if (c == '\n') {
                if (!has_unmatched_close && count == 0) {
                    puts("GOOD");
                }
                if (has_unmatched_close || count > 0) {
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

