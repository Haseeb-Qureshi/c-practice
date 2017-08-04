#include <iostream>
#include <thread>
#include <future>
#include <unistd.h>
using namespace std;

future<string> async_fetch(string name) {
  promise<string> p;
  future<string> fut = p.get_future();
  thread t([=](promise<string> p) {
    sleep(2);
    p.set_value(name);
  }, move(p));
  t.detach();
  return fut;
}

void f(string name) {
  cout << "Hello " << name << endl;
}

int main() {
  auto f1 = async([]() { sleep(1); return "Haseeb1"; });
  auto f2 = async([]() { sleep(1); return "Haseeb2"; });
  cout << f1.get() << f2.get() << endl;

  return 0;
}
