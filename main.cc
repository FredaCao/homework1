#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h>

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
	return *this;
  }

  Fraction &operator-=(const Fraction &other) {
	int new_denominator = denominator_ * other.denominator_;
	int new_numerator = numerator_ * other.denominator_ - other.numerator_ * denominator_;
	int cur_gcd = gcd(new_denominator, new_numerator);
	denominator_ = new_denominator / cur_gcd;
	numerator_ = new_numerator / cur_gcd;
	return *this;
  }

  Fraction &operator*=(const Fraction &other) {
	int new_denominator = denominator_ * other.denominator_;
	int new_numerator = numerator_ * other.numerator_;
	int cur_gcd = gcd(new_denominator, new_numerator);
	denominator_ = new_denominator / cur_gcd;
	numerator_ = new_numerator / cur_gcd;
	return *this;
  }

  bool operator==(const Fraction &other){
	return numerator_ == other.numerator_ && denominator_ == other.denominator_;
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
  if(f.denominator_ == 1){
	cout << f.numerator_;
  }
  else {
  	s << f.numerator_ << '/' << f.denominator_;
  }
  return s;
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
		  case 'x': {
			// '*'出栈
			while (!stk.empty() && stk.back() == 'x') {
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
	// 这时候需要先输入空格
	ss << " ";
	ss << stk.back();
	stk.pop_back();
  }
  return ss.str();
}

Fraction Calculate(const string &source) {
  //cout << source <<endl;
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
	} else if (numbers_ops[i] == "x") {
	  fractions[index - 2] *= fractions[index - 1];
	  fractions.pop_back();
	} else {
	  fractions.push_back(Fraction(numbers_ops[i]));
	}
  }

  return fractions[0];
}


int main(int argc, char **argv) {
  int count = 0;
  char c;
  while ((c = getopt(argc, argv, "n:")) != EOF) {
	switch (c){
	  case 'n':{
		count = atoi(optarg);
		count = count > 5 ? 5 : count;
		break;
	  }
	  default: break;
	}
  }

  string test1("8-9+3/10+6");
  string test2("5/8-2/5-4x5");
  string test3("9/10-2/5+7/8-5");
  string test4("9+10-3+7");
  string test5("3/4+1/5-2/3x1/2");
  vector<string> all;
  all.push_back(test1);
  all.push_back(test2);
  all.push_back(test3);
  all.push_back(test4);
  all.push_back(test5);

  if(count) cout << "本次共" << count <<"题，满分100分"<<endl;
  int right_count = 0;
  for(int i = 0;i<count;i++){
	cout << i << ": "<<all[i] << "=";
	string anwser;
	cin >> anwser;
	if(Fraction(anwser) == Calculate(convert_string(all[i]))){
	  cout << endl << "正确！"<<endl;
	  right_count++;
	}
	else {
	  cout << endl << "不正确。 正确答案：" <<Calculate(convert_string(all[i])) << endl;
	}
  }
  if (count)
  cout << "您的总分是" << (right_count*100/count) << "分" <<endl;


//  cout << Calculate(convert_string(test1))<<endl;
//  cout << Calculate(convert_string(test2))<<endl;
//  cout << Calculate(convert_string(test3))<<endl;
//  cout << Calculate(convert_string(test4))<<endl;
//  cout << Calculate(convert_string(test5))<<endl;

}
