#include <iostream>
#include <thread>
#include <cstdlib>
#include <unistd.h>

using namespace std;

template <typename T>
class HQueue {
private:
  int capacity;
  int start_index;
  int len;
  unique_ptr<T[]> buffer;
  int wrapped_index(int);
  mutex mut;
  condition_variable cv_not_full;
  condition_variable cv_not_empty;

public:
  HQueue(int);
  void push_back(const T&);
  T shift();
  int get_len();
};

template <typename T>
HQueue<T>::HQueue(int cap) {
  capacity = cap;
  start_index = 0;
  len = 0;
  buffer = make_unique<T[]>(capacity);
}

template <typename T>
void HQueue<T>::push_back(const T& el) {
  unique_lock<mutex> lock(mut);
  cv_not_full.wait(lock, [this]() { return len != capacity; });
  buffer[wrapped_index(len)] = el;
  len++;
  cv_not_empty.notify_one();
  cout << "Pushed " << el << " and queue size is " << len << endl;
}

template <typename T>
T HQueue<T>::shift() {
  unique_lock<mutex> lock(mut);
  cv_not_empty.wait(lock, [this]() { return len != 0; });
  T val = buffer[wrapped_index(0)];
  len--;
  start_index = wrapped_index(1);
  cv_not_full.notify_one();
  cout << "Shifted " << val << " and queue size is " << len << endl;
  return val;
}

template <typename T>
int HQueue<T>::wrapped_index(int i) {
  return (start_index + i) % capacity;
}

template <typename T>
int HQueue<T>::get_len() {
  return len;
}

int main() {

  HQueue<int> h(8);

  thread producer([&h]() {
    int i = 0;
    while (1) {
      int microseconds = 500000 * (rand() / float(RAND_MAX));
      usleep(microseconds);
      h.push_back(i);
      i++;
    }
  });

  thread consumer([&h]() {
    while (1) {
      int microseconds = 500000 * (rand() / float(RAND_MAX));
      usleep(microseconds);
      h.shift();
    }
  });

  producer.join();
  return 0;
}

// create a mutex object. std::mutex it default constructs.
// We can use mutex.lock() and mutex.unlock in your methods.

// condition_var class.
// condition_var.wait(lock, lambda)
// lambda returns true for proceed, or false for wait.
// spurious wakeup.
//
// condition_var.notify_one();
// #import <pthreads.h>


// If Itry to lock the mjtex and fail, then I ask the kernel to sleep me until someone releases the mutex.
// When someone releases the mutex, they tell the kernel. And the kernel will wake at least one of the threads waiting on the mutex.

// condition_var we're waiting not just on the mutex, but also the condition.
// Lots of people could be locking and unlocking the mutex with no change to the condition.

// Green threads: go does. Java used to do this.
// Native trheads: create kernel threads to execute the threads created in the programming language.
// Threading models. N:N: every language thread has a kernel thread. 1:N: all language threads run on the same kernel thread. M:N: more than one kernel threaed, but not every language thread gets it's own kernel thread (this is Go when MAX_THREADS > 1).
// Node and MRI have a "background thread" for doing IO. And when you start IO, it is performed in this background thread. The green thread is paused, and another thrad can run. We only need one IO thread. We can use async IO to ask the kernel to be performing multiple IO operations in parallel, and to let us know when each is complete.

// Implement greenthreads.
