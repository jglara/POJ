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
#include <sstream>
#include <string>


int main(int argc, char *argv[])
{
	int nlines(0);
	std::string line;

	// Read input: A single integer N
	{
		getline(std::cin, line);
		std::stringstream myStream(line);
		myStream >> nlines;
	}

	 for(int i=0; i<nlines; i++) {

		 // read characters and feed the acumulator

		 getline(std::cin, line);
		 std::stringstream myStream(line);
		 std::string first_number;
		 std::string second_number;

		 myStream >> first_number;
		 myStream >> second_number;

		 std::string::iterator it_first = first_number.begin();
		 std::string::iterator it_second = second_number.begin();

		 //std::cout << "Adding " << first_number  << " + " << second_number << std::endl;

		 int pos=0;
		 int carry=0;
		 while (true) {

			 int digit_1(0);
			 int digit_2(0);

			 bool advanced=false;
			 if (it_first != first_number.end()) {
				 digit_1 = *it_first - '0';
				 it_first ++;
				 advanced = true;
			 }
			 if (it_second != second_number.end()) {
				 digit_2 = *it_second - '0';
				 it_second ++;
				 advanced = true;
			 }

			 if (!advanced) {
				 if (carry) {
					 std::cout << carry;
				 }
				 break;
			 }


			 int sum = digit_1 + digit_2 + carry;
			 carry = 0;

			 if (sum < 10) {
				 std::cout << sum;
				 ++pos;
			 } else if (sum == 10) {
				 if (pos > 0 ) {
					 std::cout << 0;
				 }
				 carry = 1;
			 } else {
				 std::cout << sum - 10;
				 carry =1;
				 ++pos;
			 }




		 }


		 std::cout << std::endl;




	 }

}




/*
class ReverseAcumulator {

public:
	ReverseAcumulator() : acum_(0), power_(1), state_(INIT_REMOVE_ZEROES) { }
	unsigned long getResult() const { return acum_; }

	void addDigit(char d) {
		std::cout << "state_ " << state_
				<< ". power_ " << power_
				<< ". acum_ " << acum_
				<< ". Adding '" << d << "'"
				<< std::endl;

		switch (state_) {
		case INIT_REMOVE_ZEROES:
		{
			switch (d) {
			case '0':
				break; // ignore leading zeroes
			default:
				acum_ += power_ * (d- '0');
				power_ *= 10;
				state_ = ADD_DIGITS;
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
				acum_ += power_ * (d-'0');
				power_ *= 10;
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
*/
