#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>

#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable g_cond[2];
std::mutex g_mutex;

void funcA(bool odd)
{
  // odd thread starts from 1
  // even thread starts from 2
  for (int i = (odd ? 1 : 2) ; i <= 100; i += 2) {
    if (i > 1) {
      std::unique_lock<std::mutex> lock(g_mutex);
      g_cond[odd ? 1 : 0].wait(lock);
    }
    std::cout << std::this_thread::get_id() << " " << (odd ? "odd " : "even") << " : " << i << std::endl;

    // notify opposite side
    g_cond[odd ? 0 : 1].notify_all();
  }
}

int main(int argc, char* argv[])
{
  std::thread* t1 = new std::thread(funcA, true);
  std::thread* t2 = new std::thread(funcA, false);

  t1->join();
  t2->join();

  return 0;
}
