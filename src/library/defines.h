#ifndef SRC_LIBRARY_DEFINES_H
#define SRC_LIBRARY_DEFINES_H

#include <opencv2/core/core.hpp>
#include <vector>

typedef cv::Rect Face;
// Support not only mankind :)
typedef std::vector<cv::Rect> Mouths;
typedef std::vector<cv::Rect> Eyes;

typedef struct {
  Face face_;
  Eyes eyes_;
  Mouths mouths_;
}Head;

typedef std::vector<Head> People;

#ifdef __linux__ 
const char kDirSeparators[] = "/";
#else // Unix
const char kDirSeparators[] = "/\\";
#endif

typedef std::vector<std::string> ImagesPathes;

#endif SRC_LIBRARY_DEFINES_H