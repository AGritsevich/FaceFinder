#ifndef SRC_LIBRARY_SAVEDATA_H
#define SRC_LIBRARY_SAVEDATA_H

#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>
#include "jsonxx.h"
#include "defines.h"

class JsonAdapter {
private:
  static jsonxx::Array PrepareJson(People& people);

public:
  static bool SaveJson(People& people, const std::string& path);
};

class FilesystemHelper {
public:
  static std::string ExtractFileName(std::string full_path);
  static std::string ExtractPath(std::string full_path);
  static ImagesPathes GetAllImagesInFolder(std::string& path);
};

bool comparator(const Head& lhs, const Head& rhs);

#endif // SRC_LIBRARY_SAVEDATA_H