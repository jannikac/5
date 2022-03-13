#include "assembly3.cpp"
#include "c_exception.cpp"
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