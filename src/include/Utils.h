#ifndef SRC_LIBRARY_INCLUDE_SAVEDATA_H
#define SRC_LIBRARY_INCLUDE_SAVEDATA_H

#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>
#include "jsonxx.h"
#include "defines.h"

class JsonAdapter {
private:
  static jsonxx::Array PrepareJson(const AsyncDataList& people);

public:
  static bool SaveJson(const AsyncDataPair& data);
};

class FilesystemHelper {
public:
  static std::string ExtractFileName(const std::string& full_path);
  static std::string ExtractPath(const std::string& full_path);
  static void GetAllImagesInFolder(const char *root_path, std::vector<cv::String>& imgs);
};

#endif // SRC_LIBRARY_INCLUDE_SAVEDATA_H
