
#include "JsonAdapter.h"

jsonxx::Array JsonAdapter::PrepareJson(People& people, const std::string& file_name) {
  jsonxx::Array result;
  result << "file_name" << file_name;

  for (Head man:people) {
    jsonxx::Object face;
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


  bool JsonAdapter::SaveJson(People& people, const std::string& name, const std::string& path) {
  std::ofstream output_file(path + "result.json");

  if (!output_file) {
    return false;
  }

  jsonxx::Array json = PrepareJson(people, name);

  output_file << json.write(jsonxx::JSON);

  output_file.close();

  return true;
}