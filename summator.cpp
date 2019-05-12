#include <bits/stdc++.h>
using namespace std;

std::string input;
int now = 0;

// Declare
int get_addend();
int get_sum();

bool is_digit(char c) { return '0' <= c && c <= '9'; }

int get_value() {
  int value = 0;
  while (is_digit(input[now])) {
    value = value * 10 + (input[now] - '0');
    now++;
  }
  return value;
}

void throw_error() {
  cerr << "Unexpecter character '" << input[now - 1] << "' at " << now - 1
       << endl;
  exit(-1);
}

void throw_bracket_error() {
  cerr << "Excepted ')' symbol at " << now << endl;
  exit(-1);
}

int get_addend() {
  int value = 0;
  char current = input[now];
  if (is_digit(current)) {
    value = get_value();
  } else if (now >= int(input.size())) {
    return value;
  } else {
    now++;
    switch (current) {
    case '(':
      value = get_sum();
      if (input[now] != ')')
        throw_bracket_error();
      now++;
      break;
    case ' ':
    case '+':
      value = get_addend();
      break;
    case '-':
      value = -get_addend();
      break;
    default:
      throw_error();
      break;
    }
  }
  return value;
}

int get_sum() {
  int value = get_addend();
  while (now < int(input.size())) {
    char current = input[now];
    switch (current) {
    case ' ':
    case '+':
    case '-':
      value += get_addend();
      break;
    case ')':
      return value;
      break;
    default:
      throw_error();
      break;
    }
  }
  return value;
}

int main() {
  getline(cin, input);
  cout << get_sum() << endl;
  return 0;
}
