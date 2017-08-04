#include <iostream>
#include <vector>
#include "hvec.h"
using namespace std;

namespace haseeb {
  template <typename T>
  T max(T a, T b);
}

template <typename T>
T haseeb::max(T a, T b) {
  return a > b ? a : b;
}

int main() {
  HVector<int> nums;
  HVector<int> nums2 = nums;

  while (true) {
    string line;
    cout << "Please enter a number, or press enter when finished." << endl;
    getline(cin, line);
    if (line == "") {
      break;
    } else {
      nums.push_back(stoi(line));
    }
  }

  int maxVal = nums[0];

  nums.each([&maxVal](int num) {
    maxVal = haseeb::max(maxVal, num);
    // cout << num << " ";
  });

  cout << endl;

  nums.map([](int num) {
    return num * 2;
  }).each([](int num) {
    cout << num << " ";
  });

  cout << endl;

  cout << "Max value was " << maxVal;
  cout << endl;
  nums2 = nums;
  cout << nums2.count();
  return 0;
}
