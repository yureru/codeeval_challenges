#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nums.h"

const char *onedgt[] = {"", "One", "Two", "Three", "Four", "Five",
			"Six", "Seven", "Eight", "Nine"};
const char *twodgt[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
			"Sixteen", "Seventeen", "Eighteen", "Nineteen", "Twenty",
			"Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty",
			"Ninety"};
const char *miscdgt[] = {"Hundred", "Thousand", "Million", "Billion", "Dollars"};
 
// Prototypes
void formonedgt(struct number *num);
void formtwodgt(struct number *num);
void formthreedgt(struct number *num);
void formnumber(struct number *num);
void formbillion(struct number *num);
void unit(struct number *num, short lnqt);
unsigned thousandhelper(unsigned nqt_static, short lnqt);
unsigned millionhelper(unsigned nqt, unsigned static_numqt);
unsigned ntd(struct number *num);

// Definitions
/* calcnum
 * Description: Used to call formnumber() until quantity of digits is more than
 * the current position.
 * Returns: Nothing.
 */
void calcnum(struct number *num)
{
	unsigned nqt = num->numqt;
	while (num->pos < nqt)
		formnumber(num);
	strcat(num->str, miscdgt[4]);
}

/* initnumber
 * Description: Initializes the struct number with the corresponding parameters.
 * Everytime is called the struct is cleaned, except for the string, which the 
 * memory is reused (it's cleaned on sctnum.str[0] = '\0'; in main).
 * Parameters: Pointer to struct number, pointer to array, sv (size of vector),
 * pos the position (discard this, it's silly, use literal), str pointer to array
 * of char, ss size max of char array, qt quantity of digits in the number.
 * Returns: Nothing
 */
void initnumber(struct number *num, const unsigned *vec, size_t sv,
		size_t pos, const char *str, size_t ss, unsigned qt)
{
	num->numqt        = qt;
	num->static_numqt = qt;
	num->vecint       = vec;
	num->pos          = pos;
	num->vecintsize   = sv;
	num->str          = (char *)str;
	num->strsize      = ss;
}

/* Forms a one digit number */
void formonedgt(struct number *num)
{
	strcat(num->str, onedgt[num->vecint[num->pos]]); 
	++(num->pos);
}

/* formtwodgt
 * Description: Forms a two digit number, example 84 => "EightyFour"
 * Parameters: Pointer to struct number.
 * Returns: Nothing.
 */
void formtwodgt(struct number *num)
{
	unsigned curnum = num->vecint[num->pos], cnmult = curnum * 10;
	cnmult += num->vecint[num->pos + 1];
	if (!curnum) {
		++(num->pos);
		formonedgt(num);
	} else if (cnmult > 9 && cnmult < 20) {
		strcat(num->str, twodgt[cnmult - 10]);
		num->pos += 2;
	} else {
		strcat(num->str, twodgt[curnum + 8]);
		++(num->pos);
		formonedgt(num);
	}
}

/* formthreedgt
 * Description: Forms a three digit number, example 132 => "OneHundredThirtyTwo"
 * Parameters: Pointer to struct number.
 * Returns: Nothing.
 */
void formthreedgt(struct number *num)
{
	unsigned curnum = num->vecint[num->pos];
	if (!curnum) {
		++(num->pos);
		formtwodgt(num);
	} else { 
		formonedgt(num);
		strcat(num->str, miscdgt[0]);
		formtwodgt(num);
	}
}

/* formbillion
 * Description: If number has 10 digits, it can only be a billion, so this
 * appends the words "One" and "Billion", and increases the pos.
 * Parameters: Pointer to struct number.
 * Returns: Nothing.
 */
void formbillion(struct number *num)
{
	strcat(num->str, onedgt[1]);
	strcat(num->str, miscdgt[3]);
	num->pos = 10; // Increase to 10 for stoping loop on formnumber()
}

/* formnumber
 * Description: This selects which function to call based on the quantity of
 * digits remaining. Also decreases numqt n times, where n is the number of
 * digits that could be formed.
 * Parameters: Pointer to struct number.
 * Returns: Nothing.
 */
void formnumber(struct number *num)
{
	unsigned nqt = num->numqt;
	short lessnumqt = 0;

	switch (nqt) {
		case 1:
		case 4:
		case 7:
			formonedgt(num);
			lessnumqt = 1;
			break;
		case 2:
		case 5:
		case 8:
			formtwodgt(num);
			lessnumqt = 2;
			break;
		case 3:
		case 6:
		case 9:
			formthreedgt(num);
			lessnumqt = 3;
			break;
		case 10:
			formbillion(num);
			break;
	}
	unit(num, lessnumqt);
	if (millionhelper(num->numqt, num->static_numqt))
		strcat(num->str, miscdgt[2]);
}

/* unit
 * Description: This check if the "Thousand" words needs to be appended, for
 * example: 12533 needs to have a "Thousand" after "Twelve", but 6000000 doesn't.
 * Using helper functions like ntd(), also this decreases numqt at given quantity
 * from formnumber.
 * Parameters: Pointer to struct number, quantity of decrease numqt (lnqt).
 * Returns: Nothing.
 */
void unit(struct number *num, short lnqt)
{
	unsigned qt = num->numqt;
	switch (lnqt) {
		case 1: --(num->numqt); break;
		case 2: num->numqt -= 2; break;
		case 3: num->numqt -= 3; break;
		default: break;
	}
	switch (qt) {
		case 4:
		case 5:
		case 6:
			if (num->static_numqt > 6) {
				if (ntd(num))
					strcat(num->str, miscdgt[1]);
			} else /*if (thousandhelper(nqt_static, lnqt))*/ {
				strcat(num->str, miscdgt[1]);
			}
		break;
	}
}

/* millionhelper
 * Returns: 1 if "Million" needs to be appended based on current quantity and
 * static_numqt, 0 otherwise.
 * Parameters: nqt the current quantity, and static_numqt the const digit quantity.
 * Returns: True or false, unsigned.
 *
 */
unsigned millionhelper(unsigned nqt, unsigned static_numqt)
{
	if (nqt < 7 && nqt > 5 && static_numqt > 6)
		return 1;
	return 0;
}
/* ntd
 * Description: Check if next three numbers are positive, if so returns 1, otherwise
 * returns 0. This is used to determine if the word "Thousand" is needed to be appended.
 * Since we're decrementing num->pos this is only called when static_numqt is > 6, so 
 * there's no risk of indexing before the beggining of the array.
 * Returns: True or false, unsigned.
 */
unsigned ntd(struct number *num)
{
	// if any next three numbers aren't zero
	return num->vecint[num->pos - 3] || num->vecint[num->pos - 2] || num->vecint[num->pos - 1];
}
