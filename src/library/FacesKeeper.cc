
#include "FacesKeeper.h"
#include "defines.h"
#include "JsonAdapter.h"


std::string FacesKeeper::ExtractFileName() {
  size_t pos = full_path.find_last_of(kDirSeparators);
  std::string file_name;
  if (pos == std::string::npos) {// it's file name
    file_name = full_path;
  } else {// path
    file_name = full_path.substr(pos + 1);
  }
  return file_name;
}

std::string FacesKeeper::ExtractPath() {
  std::string path;
  size_t pos = full_path.find_last_of(kDirSeparators);
  if (pos == std::string::npos) {// it's file name
    path = ".";
  } else {// path
    path = full_path.substr(0, pos);
  }
  return path;
}

void FacesKeeper::add_man(Head man) {
  head_cluster_.push_back(man);
}

void FacesKeeper::set_path(std::string path) {
  full_path = path;
}

const std::string& FacesKeeper::path() {
  return full_path;
}

void FacesKeeper::Save() {
  std::string file_name = ExtractFileName();
  std::string path = ExtractPath();
  JsonAdapter::SaveJson(head_cluster_, file_name, path);
}

size_t FacesKeeper::Size() {
  return head_cluster_.size();
}

const People& FacesKeeper::people() {
  return head_cluster_;
} 
