#include "Simple_String.h"
#include <iostream>

using namespace std;

int main() {
  // play around with Simple_String here
  // You can cout Simple_Strings to verify things are working!

  Simple_String s1("hi");
  Simple_String s2(s1);

  cout << "c_ptr in s1: " << s1 << '\n';
  cout << "c_ptr in s2: " << s2 << '\n';
}
