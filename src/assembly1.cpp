#include <exception>
#include <memory>
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
  assembly_container(const std::vector<part> &parts)
      : assembly_ptr_(new assembly(parts)) {
    if (!assembly_ptr_->valid())
      throw invalid_assembly();
  };
  ~assembly_container() {}

private:
  std::unique_ptr<assembly> assembly_ptr_;
};