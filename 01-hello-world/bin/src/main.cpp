#include <hello_lib.hpp>

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>

int main(int argc, char* argv[]) {

  using namespace std;

  if (argc != 2) {
    throw invalid_argument("Only one argument allowed"); 
  }
  
  string arg = string(argv[argc - 1]);
  if (find_if_not(arg.begin(), arg.end(),
      [](char c) { return isdigit(c); }) != arg.end()) {
    throw invalid_argument("Only number allowed");
  }

  cout << fizzBuzz(stoi(arg)) << endl;
  
  return cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}
