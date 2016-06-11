#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <math.h>

int StrToInt(const char* S, int len)
{
  int r = 0;
  int sig = 1;
  for (int i = 0; i < len; ++i) {
    if (i == 0 && S[i] == '-') {
      sig = -1;
      continue;
    }
    r = r * 10 + S[i] - '0';
  }
  return sig * r;
}

int StrToInt2(const std::string& S)
{
  int r = 0;
  bool negative = S[0] == '-';
  for (int i = negative ? 1 : 0; i < S.length(); ++i)
    r = (r * 10) + (S[i] - '0');

  return negative ? -r : r;
}


char* IntToStr(int n)
{
  int sig = n < 0 ? -1 : 1;
  n /= sig;

  int digit = (int)log10(n) + 1;
  char* s = new char[digit + 1 + (sig < 0 ? 1 : 0)];

  if (sig < 0) {
    s[0] = '-';
  }
  else
    --digit;

  while (n != 0) {
    s[digit] = '0' + n % 10;
    --digit;
    n /= 10;
  }
  return s;
}

std::string IntToStr2(int n)
{
  bool negative = false;
  if (n < 0)
    negative = true, n = -n;

  std::string S;
  while (n != 0)
    S += '0' + n % 10, n /= 10;

  if (negative)
    S += '-';

  std::reverse(S.begin(), S.end());
  return S;
}

int main(int argc, char* argv[])
{
  std::string s1("-12345"), s2("12345");
  std::cout << StrToInt(s1.c_str(), s1.length()) << std::endl;
  std::cout << StrToInt(s2.c_str(), s2.length()) << std::endl;

  std::cout << IntToStr(-12345) << std::endl;
  std::cout << IntToStr(12345) << std::endl;
  std::cout << IntToStr2(-12345) << std::endl;
  std::cout << IntToStr2(12345) << std::endl;

  std::cout << StrToInt2(s1) << std::endl;
  std::cout << StrToInt2(s2) << std::endl;


  return 0;
}
