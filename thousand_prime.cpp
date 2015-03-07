/* Write a program which determines the sum of the first 1000 prime numbers.
 * from: https://www.codeeval.com/open_challenges/4/
 */
#include <iostream>
using std::cout; using std::endl;
int main(void)
{
	unsigned prime = 0, divisible = 0, sum = 0;
	unsigned long current = 2;
	while (prime < 1000) {
		divisible = 0;
		for (unsigned long i = 1; i <= current; ++i) {
			if (!(current % i))
				++divisible;
		}
		if (divisible == 2) {
			sum += current;
			++prime;
		}
		++current;
	}
	cout << sum;
	return 0;
}
