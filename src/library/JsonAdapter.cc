
#include "JsonAdapter.h"

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