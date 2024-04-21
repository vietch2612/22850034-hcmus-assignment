#include <cctype>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

int calculate(int a, int b, char op) {
  switch (op) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      return a / b;
  }
  return 0;
}

int evaluate(const std::string &tokens) {
  std::stack<int> nums;
  std::stack<char> operators;

  for (int i = 0; i < tokens.length(); i++) {
    if (tokens[i] == ' ') continue;

    if (isdigit(tokens[i])) {
      int val = 0;
      while (i < tokens.length() && isdigit(tokens[i])) {
        val = val * 10 + (tokens[i] - '0');
        i++;
      }
      nums.push(val);
      i--;
    }

    else {
      while (!operators.empty() &&
             precedence(operators.top()) >= precedence(tokens[i])) {
        int b = nums.top();
        nums.pop();
        int a = nums.top();
        nums.pop();
        char op = operators.top();
        operators.pop();
        nums.push(calculate(a, b, op));
      }

      operators.push(tokens[i]);
    }
  }

  while (!operators.empty()) {
    int b = nums.top();
    nums.pop();

    int a = nums.top();
    nums.pop();

    char op = operators.top();
    operators.pop();

    nums.push(calculate(a, b, op));
  }

  return nums.top();
}

int main() {
  string s = "8+3*4+2-3+4/2";
  cout << evaluate(s) << endl;
  return 0;
}