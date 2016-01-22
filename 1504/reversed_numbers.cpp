/*
 * reversed_numbers.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: ejogarv
 *
 *
 *      Description
 *
 *      The Antique Comedians of Malidinesia prefer comedies to tragedies. Unfortunately, most of the ancient plays are tragedies. Therefore the dramatic advisor of ACM has decided to transfigure some tragedies into comedies. Obviously, this work is very hard because the basic sense of the play must be kept intact, although all the things change to their opposites. For example the numbers: if any number appears in the tragedy, it must be converted to its reversed form before being accepted into the comedy play.
 *      Reversed number is a number written in arabic numerals but the order of digits is reversed. The first digit becomes last and vice versa. For example, if the main hero had 1245 strawberries in the tragedy, he has 5421 of them now. Note that all the leading zeros are omitted. That means if the number ends with a zero, the zero is lost by reversing (e.g. 1200 gives 21). Also note that the reversed number never has any trailing zeros.
 *
 *      ACM needs to calculate with reversed numbers. Your task is to add two reversed numbers and output their reversed sum. Of course, the result is not unique because any particular number is a reversed form of several numbers (e.g. 21 could be 12, 120 or 1200 before reversing). Thus we must assume that no zeros were lost by reversing (e.g. assume that the original number was 12).
 *
 *      Input
 *
 *      The input consists of N cases. The first line of the input contains only positive integer N. Then follow the cases. Each case consists of exactly one line with two positive integers separated by space. These are the reversed numbers you are to add.
 *
 *
 *      Output
 *
 *      For each case, print exactly one line containing only one integer - the reversed sum of two reversed numbers. Omit any leading zeros in the output.
 *
 *
 *      Sample Input
 *
 *      3
 *      24 1
 *      4358 754
 *      305 794
 *
 *      Sample Output
 *
 *      34
 *      1998
 *      1
 *
 */
#include <iostream>

class ReverseAcumulator {

public:
	ReverseAcumulator() : acum_(0), power_(1), state_(INIT_REMOVE_ZEROES) { }
	unsigned long getResult() const { return acum_; }

	void addDigit(char d) {
		switch (state_) {
		case INIT_REMOVE_ZEROES:
		{
			switch (d) {
			case '0':
				break; // ignore leading zeroes
			default:
				acum_ += power_ * ('0' - d); power_ *= 10;
			}
		}
		break;
		case ADD_DIGITS:
		{
			switch (d) {
			case ' ':
			{
				power_ = 1; // restart power for next number
				state_ = INIT_REMOVE_ZEROES;
			}
			break;
			default:
				acum_ += power_ * ('0' - d); power_ *= 10;
			}
		}
		break;


		}
	}

private:
	unsigned long acum_;
	unsigned int power_;
	typedef enum {
		INIT_REMOVE_ZEROES=0,
		ADD_DIGITS
	} state_t;
	state_t state_;



};

int main(int argc, char *argv[])
{
	int nlines;

	// Read input: A single integer N
	 std::cin >> nlines;

	 for(int line=0; line<nlines; line++) {

		 // read characters and feed the acumulator
		 ReverseAcumulator acum;
		 char c;
		 while (std::cin >> c) {
			 acum.addDigit(c);
		 }

		 // print acumulator output
		 std::cout << acum.getResult() << std::endl;

	 }

}




