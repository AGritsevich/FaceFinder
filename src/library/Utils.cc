
#include "Utils.h"
#include "glob.h"

jsonxx::Array JsonAdapter::PrepareJson(People& people) {
  jsonxx::Array result;

  for (Head man:people) {
    jsonxx::Object face;
    face << "file_name" << man.file_name_;
    face << "face" << man.face_.x << man.face_.y;
    for (auto mouth:man.mouths_) {
      face << "mouth" << mouth.x << mouth.y;
    }
    for (auto eye:man.eyes_) {
      face << "eyes" << eye.x << eye.y;
    }
    result << face;
  }
  return result;
}


  bool JsonAdapter::SaveJson(People& people, const std::string& path) {
  std::ofstream output_file(path + "result.json");

  if (!output_file) {
    return false;
  }

  jsonxx::Array json = PrepareJson(people);

  output_file << json.write(jsonxx::JSON);

  output_file.close();

  return true;
}

  std::string FilesystemHelper::ExtractFileName(std::string full_path) {
    size_t pos = full_path.find_last_of(kDirSeparators);
    std::string file_name;
    if (pos == std::string::npos) {// it's file name
      file_name = full_path;
    } else {// path
      file_name = full_path.substr(pos + 1);
    }
    return file_name;
  }

  std::string FilesystemHelper::ExtractPath(std::string full_path) {
    std::string path;
    size_t pos = full_path.find_last_of(kDirSeparators);
    if (pos == std::string::npos) {// it's file name
      path = ".";
    } else {// path
      path = full_path.substr(0, pos);
    }
    return path;
  }

  ImagesPathes FilesystemHelper::GetAllImagesInFolder(std::string path) {
    ImagesPathes imgs;
    glob(path + "*.jpg", imgs, true); // true - recursive
    // return sorted strings
    return imgs;
  }

  bool comparator(const Head& lhs, const Head& rhs) {
    return true;
  }