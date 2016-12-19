
#include "Utils.h"
#include <opencv2/core/utility.hpp>

jsonxx::Array JsonAdapter::PrepareJson(const AsyncDataList& people) {
  jsonxx::Array directory;

  auto save_rect = [](const std::string& name, const cv::Rect& xy)-> jsonxx::Object{
    jsonxx::Object up_struct;
    up_struct << name;
    jsonxx::Object down_struct;
    down_struct << "x" << xy.x;
    down_struct << "y" << xy.y;
    up_struct << down_struct;
    return up_struct;
  };

  for(const AsyncData& ll:people) {
    for (const Head& man:ll->data) {
      jsonxx::Object file;
      file << "file_name" << man.file_name_;
      file << save_rect("face", man.face_);
      for (auto mouth:man.mouths_) {
        file << save_rect("mouth", mouth);
      }
      for (auto eye:man.eyes_) {
        file << save_rect("eye", eye);
      }
      directory << file;
    }
  }
  return directory;
}


  bool JsonAdapter::SaveJson(const AsyncDataPair& data) {
  std::ofstream output_file(FilesystemHelper::ExtractPath(data.folder) + "result.json");

  if (!output_file) {
    return false;
  }

  jsonxx::Array json = PrepareJson(data.people_from_folder);

  output_file << json.write(jsonxx::JSON);

  output_file.close();

  return true;
}

  std::string FilesystemHelper::ExtractFileName(const std::string& full_path) {
    size_t pos = full_path.find_last_of(kDirSeparators);
    std::string file_name;
    if (pos == std::string::npos) {// it's file name
      file_name = full_path;
    } else {// path
      file_name = full_path.substr(pos + 1);
    }
    return file_name;
  }

  std::string FilesystemHelper::ExtractPath(const std::string& full_path) {
    std::string path;
    size_t pos = full_path.find_last_of(kDirSeparators);
    if (pos == std::string::npos) {// it's file name
      path = "./";
    } else {// path
      path = full_path.substr(0, pos + 1);
    }
    return path;
  }

  void FilesystemHelper::GetAllImagesInFolder(const char* root_path, std::vector<cv::String>& imgs) {
    std::string path(root_path);
      if (path.at(path.size() - 1) != kDirSeparators[0]) {
      path += kDirSeparators;
    }

    cv::glob(path + "*.*", imgs, true); // true - recursive
    // return sorted strings
  }
