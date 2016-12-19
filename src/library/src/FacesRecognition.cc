  
#include "Utils.h"
#include "FacesRecognition.h"

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <stdint.h>
#include <iostream>
 

FacesRecognition::FacesRecognition() {
//    if ( !m_fs_face_cascade_cliche.open(
//             "haarcascade_frontalface_alt.xml",
//             cv::FileStorage::READ)) {
//        throw "Can't open haarcascade_frontalface_alt.xml cascade";
//    }
//    if ( !m_fs_eyes_cascade_cliche.open(
//                "haarcascade_eye_tree_eyeglasses.xml",
//                cv::FileStorage::READ)) {
//        throw "Can't open haarcascade_eye_tree_eyeglasses.xml cascade";
//    }

//    if ( !m_fs_mouth_cascade_cliche.open(
//             "haarcascade_smile.xml",
//             cv::FileStorage::READ)) {
//        throw "Can't open haarcascade_smile.xml cascade";
//    }
}

People FacesRecognition::ThreadFacade(const std::string& path) {
  People people = CollectPeople(path);

  Notify(people.size(), path);

  return people;
}

void FacesRecognition::Notify(const size_t count, const std::string path) const {
  // print result
  std::cout << "Image processed, faces: " 
    << count
    << ", file name " 
    << path
    << std::endl;
}

cv::Mat FacesRecognition::Reflect( const cv::Mat& src ) {
  using namespace cv;
  /// Create dst, map_x and map_y with the same size as src:
  Mat dst;
  Mat map_x, map_y;
  dst.create( src.size(), src.type() );
  map_x.create( src.size(), CV_32FC1 );
  map_y.create( src.size(), CV_32FC1 );

  for( int j = 0; j < src.rows; j++ ) {
    for( int i = 0; i < src.cols; i++ ) {
      map_x.at<float>(j,i) = (float)(src.cols - i) ;
      map_y.at<float>(j,i) = (float)j ;
    }
  }

  remap( src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0) );

  return dst;
}

void FacesRecognition::SaveFace(const cv::Mat src_img, const cv::Rect face, const std::string& path, const uint16_t n) {
  // Save face
  std::string file_name = path.substr(0, path.size() - 4) + "_face_#" + std::to_string(n) + ".jpg";
  cv::Mat corp(src_img, face); // Copy?
  cv::Mat reflected_face = Reflect(corp);
  cv::imwrite(file_name, reflected_face); // CV_IMWRITE_JPEG_QUALITY
}

People FacesRecognition::CollectPeople(const std::string& image_path) {
  using namespace cv;

  //-- 1. Load the cascades
  cv::CascadeClassifier face_cascade("haarcascade_frontalface_alt.xml");
  cv::CascadeClassifier eyes_cascade("m_fs_eyes_cascade_cliche.xml");
  cv::CascadeClassifier mouth_cascade("haarcascade_smile.xml");
  
  //face_cascade.read( m_fs_face_cascade_cliche.getFirstTopLevelNode());
  //eyes_cascade.read( m_fs_eyes_cascade_cliche.getFirstTopLevelNode());
  //mouth_cascade.read( m_fs_mouth_cascade_cliche.getFirstTopLevelNode());

  {
      std::ofstream check_file;
      check_file.open (image_path, std::ios::binary| std::ios::in);
      if (!check_file.good()) {
        std::cout <<  "Could not open or find the image: " << image_path << std::endl;
        return People();
      }
  }
  //-- 2. Read the image file
  Mat src_image = imread(image_path, CV_LOAD_IMAGE_COLOR);   // Read the file

  if(!src_image.data ) // Check for invalid input
  {
    std::cout <<  "Not supported format of file: " << image_path << std::endl ;
    return People();
  }

  //-- 3. Apply the classifier to the image
  std::vector<Rect> faces;
  Mat frame_gray;

  cvtColor( src_image, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  auto i = 0;
  People people_on_photo;
  for( auto face:faces) {
    Head man;
    man.face_ = face;

    Mat faceROI = frame_gray( face );

    //-- In each face, detect eyes
    eyes_cascade.detectMultiScale( faceROI, man.eyes_, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    //-- In each face, detect mouth
    mouth_cascade.detectMultiScale( faceROI, man.mouths_, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    man.file_name_ = FilesystemHelper::ExtractFileName(image_path);
    people_on_photo.push_back(man);
    SaveFace(src_image, face, image_path, i++);
  }

  //-- Show what you got
  //imshow( "Foo", image );
  // int c = waitKey(10);
  return people_on_photo;
}
