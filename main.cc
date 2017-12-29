#include <iostream>
#include <vector>
#include <string>

using namespace std;

inline int Split(const string &src, string split_flag, vector<string> &result) {
  result.clear();

  int start_pos = 0;
  int pos = src.find(split_flag);
  while (pos != string::npos) {
	result.push_back(src.substr(start_pos, pos - start_pos));
	start_pos = pos + split_flag.length();
	pos = src.find(split_flag, start_pos);
  }

  if (start_pos < src.length()) {
	result.push_back(src.substr(start_pos));
  }

  return result.size();
}

class Fraction {
 public:
  explicit Fraction(const string &source) : numerator_(0), denominator_(1){
	vector<string> vec;
	int len = Split(source, "/", vec);
	if (len == 1){
	  numerator_ = stoi(vec[0]);
	}
	else {
	  numerator_ = stoi(vec[0]);
	  denominator_ = stoi(vec[1]);
	}
  }
  int numerator_;
  int denominator_;

  Fraction &operator+=(const Fraction &other){
	int new_denominator = denominator_ * other.denominator_;
	int new_numerator = numerator_ * other.denominator_ + other.numerator_ * denominator_;
	int cur_gcd = gcd(new_denominator, new_numerator);
	denominator_ = new_denominator / cur_gcd;
	numerator_ = new_numerator / cur_gcd;
  }

  Fraction &operator-=(const Fraction &other){
	int new_denominator = denominator_ * other.denominator_;
	int new_numerator = numerator_ * other.denominator_ - other.numerator_ * denominator_;
	int cur_gcd = gcd(new_denominator, new_numerator);
	denominator_ = new_denominator / cur_gcd;
	numerator_ = new_numerator / cur_gcd;
  }

  Fraction &operator*=(const Fraction &other){
	int new_denominator = denominator_ * other.denominator_;
	int new_numerator = numerator_ * other.numerator_;
	int cur_gcd = gcd(new_denominator, new_numerator);
	denominator_ = new_denominator / cur_gcd;
	numerator_ = new_numerator / cur_gcd;
  }

 protected:
  int gcd(int a, int b)
  {
	int c = b;
	while (a%b != 0)
	{
	  c = a%b;
	  a = b;
	  b = c;
	}
	return c < 0? -c : c;
  }

  int lcm(int a, int b){
	return a * b / gcd(a, b);
  }


};



