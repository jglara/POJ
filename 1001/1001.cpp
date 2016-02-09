//============================================================================
// Name        : 1001.cpp
// Author      : jglara
// Description : http://poj.org/problem?id=1001
//============================================================================
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <stdlib.h>

class BigNumber {
public:
  BigNumber(): num_(),power_ten_(0) {}
  BigNumber(BigNumber const &other) {
    // canonize: remove trailing and leading zeroes
    std::vector<int>::const_iterator it_begin = other.num_.begin();
    std::vector<int>::const_iterator it_end = other.num_.end();
    power_ten_ = other.power_ten_ + other.getNumZerosLeft();

    // std::cout << "new BN from " << other
    //           << ". zl=" << other.getNumZerosLeft()
    //           << ". zr=" << other.getNumZerosRight()
    //           << std::endl;
    
    num_.assign(it_begin + other.getNumZerosLeft(), it_end - other.getNumZerosRight());
  }

  BigNumber canonize() {
    std::vector<int>::const_iterator it_begin = num_.begin();
    std::vector<int>::const_iterator it_end = num_.end();

    BigNumber other;

    other.power_ten_ = power_ten_ + getNumZerosLeft();

    // std::cout << "canonize BN from " << *this
    //           << ". zl=" << getNumZerosLeft()
    //           << ". zr=" << getNumZerosRight()
    //           << std::endl;

    other.num_.assign(it_begin + getNumZerosLeft(), it_end - other.getNumZerosRight());

    return other;
  }

  BigNumber(int digits, int power_ten): num_(digits,0), power_ten_(power_ten) { }
  BigNumber(std::string str)
    {
      power_ten_ = 0;

      // store backwards and remove '.'
      for (int i=str.size()-1; i>=0; --i) {

        if (str[i] == '.') {
          power_ten_ = -(str.size() - i -1) ;
        } else {
          num_.push_back(str[i] - '0');
        }
      }
    }


  // multiply by itself
  BigNumber pow2() const
    {
      BigNumber result;
      for (unsigned int i=0; i<num_.size(); i++) {
        multiply(num_[i],i,result);
      }

      result.power_ten_ = power_ten_ * 2;
      return result;
    }

  // multiply by another number
  BigNumber multiply(BigNumber const &other) const
    {
      BigNumber result;
      for (unsigned int i=0; i<other.num_.size(); i++) {
        multiply(other.num_[i],i,result);
      }

      result.power_ten_ = power_ten_ + other.power_ten_;
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



  friend std::ostream &operator<<(std::ostream& stream, const BigNumber &bn);

private:
  std::vector<int> num_;
  int power_ten_;

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

  unsigned int getNumZerosLeft() const {
    int n=0;
    for (unsigned int i = 0; i < num_.size(); ++i) {
      if (num_[i] == 0) {
        ++ n ;
      } else {
        break;
      }
    }

    return n;
  }

  unsigned int getNumZerosRight() const {
    if (num_.empty()) return 0;

    int n=0;
    for (unsigned int i = num_.size()-1; i>0; --i) {
      if (num_[i] == 0) {
        ++ n ;
      } else {
        break;
      }
    }

    return n;
  }
};


std::ostream &operator<<(std::ostream& stream, const BigNumber &bn)
{
  // stream << "(" << bn.power_ten_ << ", " << bn.num_.size() << ") ";

  if (bn.num_.empty()) return stream;


  if ((bn.power_ten_ < 0) && (-bn.power_ten_ >= bn.num_.size())) {
    stream << '.';
    stream << std::string((-bn.power_ten_) - bn.num_.size(), '0');
  }


  int i=bn.num_.size();
  while (i>0) {
    --i;
    stream << bn.num_[i];
          
    if ((i!= 0) && (i == -bn.power_ten_)){
      stream << '.';
    }
  };

  if (bn.power_ten_ > 0) {
    stream << std::string(bn.power_ten_,'0');
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

    BigNumber result( bn.pow(pow).canonize() );
    std::cout << result << std::endl;

  }

  return 0;
}
