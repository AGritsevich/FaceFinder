#ifndef SRC_LIBRARY_FACESRECOGNITION_H
#define SRC_LIBRARY_FACESRECOGNITION_H

#include <opencv2/objdetect/objdetect.hpp>
#include <string>
#include <stdint.h>
#include "defines.h"

class FacesRecognition {
public:
  FacesRecognition();
  bool Init();
  People ThreadFacade(const std::string& path);

private:
  cv::Mat Reflect(const cv::Mat& src );
  void SaveFace(const cv::Mat src_img, const cv::Rect face, const std::string& path, const uint16_t n);
  People CollectPeople(const std::string& image_path);
  void Notify(const size_t count, const std::string path);
 
private:
  cv::FileStorage fs_face_cascade_cliche_;
  cv::FileStorage fs_eyes_cascade_cliche_;
  cv::FileStorage fs_mouth_cascade_cliche_;
};

#endif // SRC_LIBRARY_FACESRECOGNITION_H