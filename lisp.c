
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void repl(void)
{
    int ret, c, count, has_overflow, has_underflow, has_error;

    do {

        fputs("> ", stdout);

        count = 0;
        has_overflow = 0;
        has_underflow = 0;

        do {
            ret = fgetc(stdin);
            if (ret == EOF) {
                c = '\n';
            }
            if (ret != EOF) {
                c = ret;
                if (!has_underflow && !has_overflow) {
                    if (c == '(') {
                        if (count == INT_MAX) {
                            has_overflow = 1;
                        }
                        if (count < INT_MAX) {
                            count++;
                        }
                    }
                    if (c == ')') {
                        if (count == 0) {
                            has_underflow = 1;
                        }
                        if (count > 0) {
                            count--;
                        }
                    }
                }
            }
        } while (c != '\n');

        if (ret != EOF) {
            has_error = has_underflow || has_overflow || count > 0;
            if (!has_error) {
                puts("GOOD");
            }
            if (has_error) {
                puts("BAD");
            }
        }

    } while (ret != EOF);

    puts("");
    puts("BYE");
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        repl();
    }

    return 0;
}

