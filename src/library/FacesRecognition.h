#ifndef SRC_LIBRARY_FACESRECOGNITION_H
#define SRC_LIBRARY_FACESRECOGNITION_H

//#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>o
#include <string>
#include <stdint.h>
#include "FacesKeeper.h"
//#include <iostream>

class FacesRecognition {
public:
  FacesRecognition();
  People ThreadFacade(std::string& path);
  void Notify();

private:
  cv::Mat Reflect( cv::Mat& src );
  void SaveFace(cv::Rect face, uint16_t n );
  People CollectPeople(std::string image_path);

private:
  const std::string face_cascade_name;
  const std::string eyes_cascade_name;
  const std::string mouth_cascafe_name;
  cv::CascadeClassifier face_cascade;
  cv::CascadeClassifier eyes_cascade;
  cv::CascadeClassifier mouth_cascade;
  cv::Mat src_image;
  FacesKeeper people_;
};

#endif // SRC_LIBRARY_FACESRECOGNITION_H