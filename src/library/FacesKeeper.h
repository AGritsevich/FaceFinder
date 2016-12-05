
#ifndef SRC_LIBRARY_FACESKEEPER_H
#define SRC_LIBRARY_FACESKEEPER_H

#include <string>
#include "defines.h"

class FacesKeeper {
public:
  std::string ExtractFileName();
  std::string ExtractPath();
  void add_man(Head man);
  void set_path(std::string path);
  const std::string& path();
  void Save();
  size_t Size();
  const People& people();

private:
  People head_cluster_;
  std::string full_path;
};

#endif // SRC_LIBRARY_FACESKEEPER_H