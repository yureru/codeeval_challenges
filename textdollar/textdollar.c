/* Insert a positive number between 0 and 1000000000 (1 billion) and it will be
 * converted to string form. Example:
 * Enter number unsigned long: 1892334
 * String is: OneMillionEightHundredNinetyTwoThousandThreeHundredThirtyFour
 *
 * from: https://www.codeeval.com/open_challenges/52/
 */
// Flags used to compile:  -Wall -pedantic -Wextra -std=c99
#include <stdio.h>
#include <stdlib.h>
#include "nums.h"

// Prototypes
unsigned splitnum(unsigned long num, unsigned *vec);
unsigned numchar(const char *str);
void cleanvector(unsigned *vec, size_t sz);

int main(void)
{
	struct number sctnum;
	char str[100] = {'\0'};
	unsigned vec[10] = {0}, numqt = 0;
	unsigned long num = 0;
	while (1) {
		printf("Enter number unsigned long: ");
		if (scanf("%lu", &num) != 1) {
			puts("Error: Didn't enter a valid number!");
			exit(EXIT_FAILURE);
		}
		numqt = splitnum(num, vec);
		initnumber(&sctnum, vec, (sizeof(vec) / sizeof(vec[0])), 0,
				str, sizeof(str), numqt);

		calcnum(&sctnum);
		printf("String is: %s\n", sctnum.str);
		sctnum.str[0] = '\0';
	}
	return 0;
}

/* splitnum
 * Description: Saves each digit (of an unsigned long) into a position of a 
 * vector of unsigned. E.g: 13942 => [1][3][9][4][2]...
 * Parameters: The unsigned long number, pointer to the vector (array of unsigned).
 * Returns: A unsigned, the quantity of digits readed.
 */
unsigned splitnum(unsigned long num, unsigned *vec)
{
	unsigned long long mult = 1;
	unsigned long cpynum = num;
	unsigned qt = 0;
	while (cpynum) {
		cpynum /= 10;
		mult *= 10;
		++qt;
	}
	// num is a number with only 1 digit
	if (mult <= 10) {
		vec[0] = num;
		return 1;
	}
	// Divide by 10, because mult is 10 times bigger than correct value
	// cause in the first while started with 1 * 10...
	mult /= 10;
	for (unsigned i = 0; i < qt && mult; ++i) {
		*(vec + i) = num / mult;
		num -= *(vec + i) * mult;
		mult /= 10;
	}
	return qt;
}

/* numchar()
 * Description: Counts the quantity of characters in string,
 * until but including the '\n'.
 * Parameters: Pointer to null terminated string.
 * Returns: Unsigned, the count.
 */
unsigned numchar(const char *str)
{
	const char *ss = str;
	while (*str++)
		;
	return str - ss;
}

/* cleanvector
 * Description: Cleans an array.
 * Parameters: Pointer to element (first if want to clean all), and number of elements to be cleaned.
 * Returns: void.
 */
void cleanvector(unsigned *vec, size_t sz)
{
	for (size_t i = 0; i < sz; ++i)
		*(vec + i) = 0;
}
