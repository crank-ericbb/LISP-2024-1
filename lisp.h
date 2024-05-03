
#ifndef LISP_H
#define LISP_H

#include <stdlib.h>

#define LISP_STATE_READING 0
#define LISP_STATE_WAITING 1

struct lisp {
	int state;
	int has_underflow;
	int has_overflow;
	int count;
};

void lisp_init(struct lisp *lisp);

size_t lisp_read_bytes(struct lisp *lisp, size_t num_bytes, const char *bytes);

void lisp_reset(struct lisp *lisp);

#endif
