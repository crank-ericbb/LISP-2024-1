
#include <limits.h>
#include <stdlib.h>

#include "lisp.h"

void lisp_init(struct lisp *lisp)
{
	lisp->state = LISP_STATE_READING;
	lisp->has_underflow = 0;
	lisp->has_overflow = 0;
	lisp->count = 0;
}

size_t lisp_read_bytes(struct lisp *lisp, size_t num_bytes, const char *bytes)
{
	size_t i;

	for (i = 0; i < num_bytes && lisp->state == LISP_STATE_READING; i++) {
		if (bytes[i] == '\n') {
			lisp->state = LISP_STATE_WAITING;
		}
		if (bytes[i] == '(') {
			if (lisp->count == INT_MAX) {
				lisp->has_overflow = 1;
			}
			if (lisp->count < INT_MAX) {
				lisp->count++;
			}
		}
		if (bytes[i] == ')') {
			if (lisp->count == 0) {
				lisp->has_underflow = 1;
			}
			if (lisp->count > 0) {
				lisp->count--;
			}
		}
	}

	return i;
}

void lisp_reset(struct lisp *lisp)
{
	lisp->state = LISP_STATE_READING;
	lisp->has_underflow = 0;
	lisp->has_overflow = 0;
	lisp->count = 0;
}
