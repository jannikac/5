#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class my_exception_class : public std::runtime_error {
  std::string msg;

public:
  const char *what() const throw() { return msg.c_str(); }

  my_exception_class(const std::string &arg, const char *file, int line)
      : std::runtime_error(arg) {
    std::ostringstream o;
    o << file << ":" << line << ":" << arg;
    msg = o.str();
  }

  ~my_exception_class() throw() {}
};
