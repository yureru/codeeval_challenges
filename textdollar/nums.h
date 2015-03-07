#ifndef NUMS_H
#define NUMS_H
#include <stddef.h>
/*
 * Description: Saves data about a number, numqt is the quantity of digits, so
 * is static_numqt (which should never be modifyied), vecint is a pointer to
 * an unsigned array[10], pos is the position in the array, str is a pointer to
 * char array, strsize is the size of string. strsize and vecintsize are unused
 * there were intended to add security.
 */
struct number {
	unsigned numqt, static_numqt;
	const unsigned *vecint;
	size_t pos;
	size_t vecintsize;
	char *str;
	size_t strsize;
};

void initnumber(struct number *num, const unsigned *vec, size_t sv,
		size_t pos, const char *str, size_t ss, unsigned qt);

void calcnum(struct number *num);
#endif // -> NUMS_H
