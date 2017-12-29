#include <iostream>
#include <vector>
#include <sstream>

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
  Fraction(const Fraction &other) : numerator_(other.numerator_), denominator_(other.denominator_) {}

  explicit Fraction(const string &source) : numerator_(0), denominator_(1) {
	vector<string> vec;
	int len = Split(source, "/", vec);
	if (len == 1) {
	  numerator_ = stoi(vec[0]);
	} else {
	  numerator_ = stoi(vec[0]);
	  denominator_ = stoi(vec[1]);
	}
  }

  Fraction &operator=(const Fraction &other) {
	numerator_ = other.numerator_;
	denominator_ = other.denominator_;
	return *this;
  }

  int numerator_;
  int denominator_;

  Fraction &operator+=(const Fraction &other) {
	int new_denominator = denominator_ * other.denominator_;
	int new_numerator = numerator_ * other.denominator_ + other.numerator_ * denominator_;
	int cur_gcd = gcd(new_denominator, new_numerator);
	denominator_ = new_denominator / cur_gcd;
	numerator_ = new_numerator / cur_gcd;
  }

  Fraction &operator-=(const Fraction &other) {
	int new_denominator = denominator_ * other.denominator_;
	int new_numerator = numerator_ * other.denominator_ - other.numerator_ * denominator_;
	int cur_gcd = gcd(new_denominator, new_numerator);
	denominator_ = new_denominator / cur_gcd;
	numerator_ = new_numerator / cur_gcd;
  }

  Fraction &operator*=(const Fraction &other) {
	int new_denominator = denominator_ * other.denominator_;
	int new_numerator = numerator_ * other.numerator_;
	int cur_gcd = gcd(new_denominator, new_numerator);
	denominator_ = new_denominator / cur_gcd;
	numerator_ = new_numerator / cur_gcd;
  }

 protected:
  int gcd(int a, int b) {
	int c = b;
	while (a % b != 0) {
	  c = a % b;
	  a = b;
	  b = c;
	}
	return c < 0 ? -c : c;
  }

  int lcm(int a, int b) {
	return a * b / gcd(a, b);
  }

};

ostream &operator<<(ostream &s, Fraction f){
  s << f.numerator_ << '/' << f.denominator_;
}

string convert_string(const string &source) {
  stringstream ss;
  vector<char> stk;
  for (size_t i = 0; i < source.length(); i++) {
	if (source.at(i) == ' ') {
	  continue;
	} else if (isdigit(source.at(i)) || source.at(i) == '/') {
	  ss << source.at(i);
	  // 如果下一位不是数字，或者已经是最后一位，就加上空格
//	  if ((i < source.length() - 1 && !isdigit(source.at(i + 1)))
//		  || i == source.length() - 1) {
//		ss << " ";
//	  }
	} else {
	  ss << " ";
	  if (stk.empty()) {
		stk.push_back(source.at(i));
	  } else {
		switch (source.at(i)) {
		  case '+':
		  case '-': {
			// '+' '-' '*' '/'都出栈
			while (!stk.empty()) {
			  ss << stk.back();
			  ss << " ";
			  stk.pop_back();
			}
			stk.push_back(source.at(i));
			break;
		  }
		  case '*': {
			// '*'出栈
			while (!stk.empty() && stk.back() == '*') {
			  ss << stk.back();
			  ss << " ";
			  stk.pop_back();
			}
			stk.push_back(source.at(i));
			break;
		  }
		}
	  }
	}
  }
  // 最后元素需要pop出来
  while (!stk.empty()) {
	ss << stk.back();
	ss << " ";
	stk.pop_back();
  }
  return ss.str();
}

Fraction Calculate(const string &source) {
  vector<string> numbers_ops;
  vector<Fraction> fractions;
  int len = Split(source, " ", numbers_ops);
  for (int i = 0; i < len; i++) {
	int index = fractions.size();
	if (numbers_ops[i] == "+") {
	  fractions[index - 2] += fractions[index - 1];
	  fractions.pop_back();
	} else if (numbers_ops[i] == "-") {
	  fractions[index - 2] -= fractions[index - 1];
	  fractions.pop_back();
	} else if (numbers_ops[i] == "*") {
	  fractions[index - 2] *= fractions[index - 1];
	  fractions.pop_back();
	} else {
	  fractions.push_back(Fraction(numbers_ops[i]));
	}
  }

  return fractions[0];
}

