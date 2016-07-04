#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>

double Power(double x, int y)
{
  double ret = 1.0;
  if (y > 0) {
    for (int i = 0; i < y; ++i) {
      ret *= x;
    }
  }
  else if (y < 0) {
    for (int i = 0; i > y; --i) {
      ret /= x;
    }
  }
  return ret;
}

double Power2(double x, int y)
{
  double ret = 1.0;
  double m = x;
  if (y < 0) {
    m = 1.0 / x;
    y = -y;
  }
  while (y > 0) {
    ret *= m;
    --y;
  }
  return ret;
}

double Power3(double x, int y)
{
  long long power = y;
  double ret = 1.0;
  if (y < 0) {
    x = 1.0 / x;
    power = -y;
  }
  while (power) {
    if (power & 1) {
      ret *= x;
    }
    x *= x;
    power >>= 1;
  }
  return ret;
}


bool Same(double a, double b, int digit)
{
  if ((int)(a * digit) == (int)(b * digit)) {
    return true;
  }
  return false;
}

int main(int argc, char* argv[])
{
  assert(Same(Power(2.0, 3), 8.0, 2));
  assert(Same(Power(10.0, -2), 0.01, 2));
  assert(Same(Power2(2.0, 3), 8.0, 2));
  assert(Same(Power2(10.0, -2), 0.01, 2));
  assert(Same(Power3(2.0, 3), 8.0, 2));
  assert(Same(Power3(10.0, -2), 0.01, 2));


  return 0;
}
