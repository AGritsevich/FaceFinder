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

typedef cv::Rect Face;
// Support not only mankind :)
typedef std::vector<cv::Rect> Mouths;
typedef std::vector<cv::Rect> Eyes;

typedef struct {
  Face face_;
  Eyes eyes_;
  Mouths mouths_;
  std::string file_name_;
}Head;

typedef std::vector<Head> People;

typedef std::shared_ptr<AData<People>> AsyncData;
typedef std::deque<AsyncData> AsyncDataList;
typedef struct _AsyncDataPair{
  AsyncDataList people_from_folder; 
  std::string folder;
  _AsyncDataPair(AsyncDataList ll, std::string ff) {
    people_from_folder = std::move(ll);
    folder = ff;
  }
} AsyncDataPair;

#ifdef __linux__ 
const char kDirSeparators[] = "/";
#else // Unix
const char kDirSeparators[] = "\\";
#endif

typedef std::vector<std::string> ImagesPathes;

#endif SRC_LIBRARY_DEFINES_H