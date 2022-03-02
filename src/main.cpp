#include "assembly3.cpp"
#include <iostream>
#include <vector>

int main() {
  // parts
  std::vector<part> asd{};
  // main func
  try {
    assembly_container a = {asd};
  } catch (const std::exception &) {
    std::cout << "exit";
  }
  return 0;
}