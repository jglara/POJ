//============================================================================
// Name        : 1001.cpp
// Author      : jglara
// Description : http://poj.org/problem?id=1001
//============================================================================
#include <iostream>
#include <string>
#include <vector>

class BigNumber {
public:
	BigNumber(): num_(),num_decimals_(0) {}
	BigNumber(BigNumber const &other) {
		// canonize: remove trailing and leading zeroes
		std::vector<int>::const_iterator it_begin = other.num_.begin();
		std::vector<int>::const_iterator it_end = other.num_.end();

		num_decimals_ = other.num_decimals_;
		for (unsigned int i = 0; i < other.num_decimals_; ++i) {
			if (other.num_[i] == 0) {
				++ it_begin ;
				-- num_decimals_ ;
			} else {
				break;
			}
		}

		for (int i = other.num_.size()-1; i > other.num_decimals_; --i) {
			if (other.num_[i] == 0) {
				-- it_end ;
			} else {
				break;
			}
		}
		num_.assign(it_begin,it_end);
	}

	BigNumber &operator=(BigNumber const &other) {
		if (this == &other) return *this;

		// canonize: remove trailing and leading zeroes
		std::vector<int>::const_iterator it_begin = other.num_.begin();
		std::vector<int>::const_iterator it_end = other.num_.end();

		num_decimals_ = other.num_decimals_;
		for (unsigned int i = 0; i < other.num_decimals_; ++i) {
			if (other.num_[i] == 0) {
				++ it_begin ;
				-- num_decimals_;
			} else {
				break;
			}
		}

		for (unsigned int i = other.num_.size(); i >= other.num_decimals_; --i) {
			if (other.num_[i] == 0) {
				-- it_end ;
			} else {
				break;
			}
		}


		num_.assign(it_begin,it_end);


		return *this;
	}

	BigNumber(int digits, int decimals): num_(digits,0), num_decimals_(decimals) { }
	BigNumber(std::string str)
	{
		num_decimals_ = 0;

		// store backwards and remove '.'
		for (int i=str.size()-1; i>=0; --i) {

			if (str[i] == '.') {
				num_decimals_ = str.size() - i -1 ;
			} else {
				num_.push_back(str[i] - '0');
			}
		}
	}

	// multiply by a digit, sum to acum starting by pos
	void multiply(int digit, int shift, BigNumber &acum) const
	{

		acum.num_.resize(num_.size() + shift, 0);

		unsigned int carry=0;
		for (unsigned int i=0; i<num_.size(); i++) {
			unsigned int temp = digit  * num_[i] + carry + acum.num_[i+shift];
			acum.num_[i+shift] = temp % 10;
			carry = temp / 10;
		}

		while (carry > 0) {
			acum.num_.push_back(carry % 10);
			carry = carry / 10;
		}

	}

	// multiply by itself
	BigNumber pow2() const
	{
		BigNumber result;
		for (unsigned int i=0; i<num_.size(); i++) {
			multiply(num_[i],i,result);
		}

		result.num_decimals_ = num_decimals_ * 2;
		return result;
	}

	// multiply by another number
	BigNumber multiply(BigNumber const &other) const
	{
		BigNumber result;
		for (unsigned int i=0; i<other.num_.size(); i++) {
			multiply(other.num_[i],i,result);
		}

		result.num_decimals_ = num_decimals_ + other.num_decimals_;
		return result;

	}

	// power to the n
	BigNumber pow(unsigned int n) const
	{

		if (n==1) {
			return *this;
		} else if (n==2) {
			return pow2();
		}

		BigNumber temp(pow(n/2));;
		BigNumber temp2(temp.pow2());

		if ((n%2) == 0) {
			return temp2;
		} else {
			return temp2.multiply(*this);
		}
	}



	friend std::ostream &operator<<(std::ostream& stream, BigNumber &bn);

private:
	std::vector<int> num_;
	unsigned int num_decimals_;
};


std::ostream &operator<<(std::ostream& stream, BigNumber &bn)
{
	//stream << "(" << bn.num_decimals_ << ", " << bn.num_.size() << ") ";

	int i=bn.num_.size()-1;
	if (bn.num_[i] == 0 && bn.num_decimals_ == i) {
		stream << '.';
		--i;
	}

	for (; i>=0; --i) {
		stream << bn.num_[i];

		if ((i == bn.num_decimals_)  && (bn.num_decimals_ > 0)){
			stream << '.';
		}
	}


	return stream;

}



///////////////////////////////////////////////////////7
int main(void) {

	std::string base;
	unsigned int pow;
	while(std::cin>>base>>pow) {
		//std::cout << base << "^" << pow_ << std::endl;

		BigNumber bn(base);
		//std::cout << bn << "^" << pow << std::endl;

		BigNumber result( bn.pow(pow) );
		std::cout << result << std::endl;

	}

	return 0;
}
