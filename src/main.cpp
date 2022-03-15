#include "assembly3.cpp"
#include "c_exception.cpp"
#include "string.hpp"
#include <iostream>
#include <ostream>
#include <vector>
#define throw_myclass(args) throw my_exception_class(args, __FILE__, __LINE__);

int main() {
  // parts
  // std::vector<part> asd{};
  // main func
  try {
    // assembly_container a = {asd};
    throw_myclass("Ueber Stoeckchen gestolpert!");
  } catch (const std::exception &e) {
    std::cout << e.what() << "\n"
              << "exit" << std::endl;
  }
  return 0;
}

void string_test() {
  try {
    string test;
    test.find('a');
    test.print();
    test.append("a");

    string test2 = test;
    test.clear();
    test2.print();

    string test3(std::move(test2));
    string result = string("a") + string("b") + string("c");
    result.print();
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}