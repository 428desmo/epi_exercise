#include <iostream>
#include <cstdio>
#include <assert.h>

uint64_t SwapBit(uint64_t x, int i, int j)
{
  uint64_t x_i = (x >> i) & 1;
  uint64_t x_j = (x >> j) & 1;
  uint64_t y = (x ^ (x_i << i) ^ (x_j << j)) | (x_j <<i ) | (x_i << j);
  return y;
}

uint64_t SwapBit2(uint64_t x, int i, int j)
{
  if (((x >> i) & 1) != ((x >> j) & 1)) {
    uint64_t bitMask = ((uint64_t)1 << i) + ((uint64_t)1 << j);
    x ^= bitMask;
  }
  return x;
}


int main()
{
  assert(SwapBit(0x0000000000000000, 0, 63) == 0x0000000000000000);
  assert(SwapBit(0xffff000000000000, 0, 63) == 0x7fff000000000001);
  assert(SwapBit(0xffff000000000000, 4, 63) == 0x7fff000000000010);
  assert(SwapBit(0xffff000000000000, 9, 62) == 0xbfff000000000200);

  assert(SwapBit2(0x0000000000000000, 0, 63) == 0x0000000000000000);
  assert(SwapBit2(0xffff000000000000, 0, 63) == 0x7fff000000000001);
  assert(SwapBit2(0xffff000000000000, 4, 63) == 0x7fff000000000010);
  assert(SwapBit2(0xffff000000000000, 9, 62) == 0xbfff000000000200);

  return 0;
}
