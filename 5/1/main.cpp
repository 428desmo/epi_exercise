#include <iostream>
#include <deque>
#include <assert.h>

int Parity0(uint64_t x)
{
  int p = 0;
  while (x) {
    p ^= (x & 1);
    x >>= 1;
  }
  return p;
}

int Parity1(uint64_t x)
{
  int p = 0;
  while (x) {
    p ^= 1;
    x &= (x - 1);
  }
  return p;
}

int Parity2(uint64_t x)
{
  x = (x & 0xffffffff) ^ (x >> 32);
  x = (x & 0xffff) ^ (x >> 16);
  x = (x & 0xff) ^ (x >> 8);
  x = (x & 0xf) ^ (x >> 4);
  x = (x & 0x3) ^ (x >> 2);
  x = (x & 0x1) ^  (x >> 1);

  return x ? 1 : 0;
}

int Parity3(uint64_t x)
{
  static int pre_known[16] = { 0,   //(0000)
                               1,   //(0001)
                               1,   //(0010)
                               0,   //(0011)
                               1,   //(0100)
                               0,   //(0101)
                               0,   //(0110)
                               1,   //(0111)
                               1,   //(1000)
                               0,   //(1001)
                               0,   //(1010)
                               1,   //(1011)
                               0,   //(1100)
                               1,   //(1101)
                               1,   //(1110)
                               0 }; //(1111)


  x = (x & 0xffffffff) ^ (x >> 32);
  x = (x & 0xffff) ^ (x >> 16);
  x = (x & 0xff) ^ (x >> 8);
  x = (x & 0xf) ^ (x >> 4);
  return pre_known[x];
}

int g_cache[0x10000]; // 65536
void preload()
{
  for (int i = 0; i < 0x10000; ++i) {
    g_cache[i] = Parity3(i);
  }
}

int Parity4(uint64_t x)
{
  x = (x & 0xffffffff) ^ (x >> 32);
  x = (x & 0xffff) ^ (x >> 16);
  return g_cache[x];
}

int Parity5(uint64_t x)
{
  x ^= (x >> 32);
  x ^= (x >> 16);
  x ^= (x >> 8);
  x ^= (x >> 4);
  x ^= (x >> 2);
  x ^= (x >> 1);

  return x & 1;
}

int main(int argc, char* argv[])
{
  int m = -1;
  int n = 100;
  if (argc > 1) {
    m = atoi(argv[1]);
  }
  if (argc > 2) {
    n = atoi(argv[2]);
  }

  int i = 0;
  uint64_t r = 0;

  switch(m) {
    case 0:
      for (i = 0; i < n; ++i) {
        r = ((uint64_t)rand() << 32) + rand();
        Parity0(r);
      }
      break;
    case 1:
      for (i = 0; i < n; ++i) {
        r = ((uint64_t)rand() << 32) + rand();
        Parity1(r);
      }
      break;
    case 2:
      for (i = 0; i < n; ++i) {
        r = ((uint64_t)rand() << 32) + rand();
        Parity2(r);
      }
      break;
    case 3:
      for (i = 0; i < n; ++i) {
        r = ((uint64_t)rand() << 32) + rand();
        Parity3(r);
      }
      break;
    case 4:
      preload();
      for (i = 0; i < n; ++i) {
        r = ((uint64_t)rand() << 32) + rand();
        Parity4(r);
      }
      break;
    case 5:
      for (i = 0; i < n; ++i) {
        r = ((uint64_t)rand() << 32) + rand();
        Parity5(r);
      }
      break;
    default:
      assert(Parity0(0x00000000) == 0);
      assert(Parity0(0x00000001) == 1);
      assert(Parity0(0x00010000) == 1);
      assert(Parity0(0x01001000) == 0);
      assert(Parity0(0x10001100) == 1);
      assert(Parity0(0x00111100) == 0);
      assert(Parity0(0x10001100) == 1);
      assert(Parity0(0x11111111) == 0);

      for (i = 0; i < 100; ++i) {
        r = ((uint64_t)rand() << 32) + rand();
        assert(Parity0(r) == Parity1(r));
        assert(Parity0(r) == Parity2(r));
        assert(Parity0(r) == Parity3(r));
        preload();
        assert(Parity0(r) == Parity4(r));
        assert(Parity0(r) == Parity5(r));
      }
      break;
  }
  return 0;
}
