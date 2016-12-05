#ifndef SRC_LIBRARY_SAVEDATA_H
#define SRC_LIBRARY_SAVEDATA_H

#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>
#include "jsonxx.h"
#include "FacesKeeper.h"

class JsonAdapter {
private:
  static jsonxx::Array PrepareJson(People& people, const std::string& file_name);

public:
  static bool SaveJson(People& people, const std::string& name, const std::string& path);
};

#endif // SRC_LIBRARY_SAVEDATA_H