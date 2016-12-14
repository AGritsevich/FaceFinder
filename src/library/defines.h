#ifndef SRC_LIBRARY_DEFINES_H
#define SRC_LIBRARY_DEFINES_H

#include <opencv2/core/core.hpp>
#include <vector>
#include <string>
#include <memory>
#include <deque>

template<class _T>
struct AData {
  AData():ready(false){}
  bool ready;
  _T data;
};

struct Head{
  cv::Rect face_;
  std::vector<cv::Rect> eyes_;
  std::vector<cv::Rect> mouths_;
  std::string file_name_;
};

using People = std::vector<Head>;

using AsyncData = std::shared_ptr<AData<People>>;
using AsyncDataList = std::deque<AsyncData>;
struct AsyncDataPair{
  AsyncDataList people_from_folder; 
  std::string folder;
  AsyncDataPair(AsyncDataList ll, std::string ff) {
    people_from_folder = std::move(ll);
    folder = ff;
  }
};

#ifdef __linux__ 
const char kDirSeparators[] = "/";
#else // Windows
const char kDirSeparators[] = "\\";
#endif

using ImagesPathes = std::vector<std::string>;

#endif SRC_LIBRARY_DEFINES_H