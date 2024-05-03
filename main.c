
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lisp.h"

static void prompt(void)
{
	if (isatty(fileno(stdin))) {
		printf("> ");
	}
}

static void repl(void)
{
	struct lisp lisp;
	char buffer[256];
	int has_error;
	size_t i, num_bytes;
	const char *s;

	prompt();
	lisp_init(&lisp);

	while (1) {
		s = fgets(buffer, sizeof(buffer), stdin);
		if (s == NULL) {
			break;
		}
		num_bytes = strlen(s);
		i = 0;
		do {
			i += lisp_read_bytes(&lisp, num_bytes - i, &buffer[i]);
			if (lisp.state == LISP_STATE_WAITING) {
				has_error = lisp.has_underflow || lisp.has_overflow || lisp.count > 0;
				if (!has_error) {
					puts("GOOD");
				}
				if (has_error) {
					puts("BAD");
				}
				prompt();
				lisp_reset(&lisp);
			}
		} while (i < num_bytes);
	}

	if (isatty(fileno(stdin))) {
		puts("");
	}
	puts("BYE");
}

int main(int argc, char **argv)
{
	if (argc == 1) {
		repl();
	}

	return 0;
}
