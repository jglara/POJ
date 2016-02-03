//============================================================================
// Name        : 1001.cpp
// Author      : jglara
// Description : http://poj.org/problem?id=1001
//============================================================================
#include <iostream>


int main(void) {

	float base;
	unsigned int pow_;
	while(std::cin>>base>>pow_) {
		std::cout << base << "^" << pow_ << std::endl;
	}

	return 0;
}
