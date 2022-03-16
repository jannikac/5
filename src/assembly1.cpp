#include <exception>
#include <vector>
class part {};
class assembly {
public:
  assembly(const std::vector<part> &parts){};
  bool valid() { return false; }
};

class invalid_assembly : public std::exception {};

class assembly_container {
public:
  assembly_container(const std::vector<part> &parts) : assem(assembly(parts)) {
    if (!assem.valid())
      throw invalid_assembly();
  };
  ~assembly_container() {}

private:
  assembly assem;
};