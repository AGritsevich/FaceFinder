
#include "Utils.h"
#include "glob.h"

jsonxx::Array JsonAdapter::PrepareJson(const AsyncDataList& people) {
  jsonxx::Array directory;

  auto save_rect = [](const std::string& name, cv::Rect xy)-> jsonxx::Object{
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
      path = "./";
    } else {// path
      path = full_path.substr(0, pos + 1);
    }
    return path;
  }

  ImagesPathes FilesystemHelper::GetAllImagesInFolder(std::string& path) {
    ImagesPathes imgs;
    if (path.at(path.size() - 1) != kDirSeparators[0]) {
      path += kDirSeparators;
    }

    glob(path + "*.*", imgs, true); // true - recursive
    // return sorted strings
    return imgs;
  }

  bool comparator(const Head& lhs, const Head& rhs) {
    if (0 <= lhs.file_name_.compare(rhs.file_name_)) {
      return true;
    }

    if (lhs.face_.size().height > rhs.face_.size().height) {
      return true;
    }

    if (lhs.face_.size().width > rhs.face_.size().width) {
      return true;
    }

    return true;
  }