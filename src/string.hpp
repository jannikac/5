#ifndef INCLUDED__MCPP__STRING_HPP
#define INCLUDED__MCPP__STRING_HPP
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string.h>

class string {
private:
  char *str;
  int length;

public:
  string();
  string(const char *inputString);
  // Copy Konstruktor
  string(const string &other);
  // Move Konstruktor
  string(string &&other);
  void append(const char *inputString);
  // Verkettet 2 Strings miteinander
  string operator+(const string &other);
  // lvalue -> schreibend
  char &operator[](const int index);
  char &at(const int index);
  // rvalue -> lesend
  const char &operator[](const int index) const;
  const char &at(const int index) const;
  char *data();
  const char *data() const;
  int find(char c) const;
  void print() const;
  void clear();
  ~string();
};

#endif