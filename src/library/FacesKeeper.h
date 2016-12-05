
#ifndef SRC_LIBRARY_FACESKEEPER_H
#define SRC_LIBRARY_FACESKEEPER_H

#include <string>
#include "defines.h"

class FacesKeeper {
public:
  static std::string ExtractFileName(std::string full_path);
  static std::string ExtractPath(std::string full_path);
  void add_man(Head man);
  void set_path(std::string path);
  const std::string& path();
  size_t Size();
  const People& people();

private:
  People head_cluster_;
  std::string full_path_;
};

#endif // SRC_LIBRARY_FACESKEEPER_H