#ifndef SRC_LIBRARY_FACESRECOGNITION_H
#define SRC_LIBRARY_FACESRECOGNITION_H

#include <opencv2/objdetect/objdetect.hpp>
#include <string>
#include <stdint.h>
#include "defines.h"

class FacesRecognition {
public:
  FacesRecognition();
  People ThreadFacade(const std::string& path);

private:
  cv::Mat Reflect(const cv::Mat& src );
  void SaveFace(const cv::Rect face, const std::string& path, const uint16_t n);
  People CollectPeople(const std::string& image_path);
  void Notify(const size_t count, const std::string path);

private:
  const std::string face_cascade_name;
  const std::string eyes_cascade_name;
  const std::string mouth_cascafe_name;
  cv::CascadeClassifier face_cascade;
  cv::CascadeClassifier eyes_cascade;
  cv::CascadeClassifier mouth_cascade;
  cv::Mat src_image;
};

#endif // SRC_LIBRARY_FACESRECOGNITION_H