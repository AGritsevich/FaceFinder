
#include "FacesRecognition.h"
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <stdint.h>
#include <iostream>
#include "defines.h"
 

FacesRecognition::FacesRecognition() :
  face_cascade_name("haarcascade_frontalface_alt.xml"),
  eyes_cascade_name("haarcascade_eye_tree_eyeglasses.xml"),
  mouth_cascafe_name("haarcascade_mcs_mouth.xml") {
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ 
      std::cout << "--(!)Error loading face cascade\n"; 
    };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ 
      std::cout << "--(!)Error loading eyes cascade\n";  
    };
    if( !mouth_cascade.load( mouth_cascafe_name ) ){ 
      std::cout << "--(!)Error loading mouth cascade\n"; 
    };
}

void FacesRecognition::ThreadFacade(std::string& path) {
  people_.set_path(path);

  if (!ReadImage(path)) {
    return;
  }

  CollectPeople();

  people_.Save();

  Notify();
}

bool FacesRecognition::ReadImage(std::string image_path) {
  using namespace cv;

  //-- 2. Read the image file
  src_image = imread(image_path, CV_LOAD_IMAGE_COLOR);   // Read the file

  if(!src_image.data )                              // Check for invalid input
  {
    std::cout <<  "Could not open or find the image" << std::endl ;
    return false;
  }
  return true;
}

void FacesRecognition::Notify() {
  // print result
  std::cout << "Image processed, faces: " 
    << people_.Size() 
    << ", file name " 
    << people_.path()
    << std::endl;
}

cv::Mat FacesRecognition::Reflect( cv::Mat& src ) {
  using namespace cv;
  /// Create dst, map_x and map_y with the same size as src:
  Mat dst;
  Mat map_x, map_y;
  dst.create( src.size(), src.type() );
  map_x.create( src.size(), CV_32FC1 );
  map_y.create( src.size(), CV_32FC1 );

  for( int j = 0; j < src.rows; j++ ) {
    for( int i = 0; i < src.cols; i++ ) {
      //map_x.at<float>(j,i) = (float)i ;
      //map_y.at<float>(j,i) = (float)(src.rows - j) ;

      map_x.at<float>(j,i) = (float)(src.cols - i) ;
      map_y.at<float>(j,i) = (float)j ;

      //map_x.at<float>(j,i) = (float)(src.cols - i) ;
      //map_y.at<float>(j,i) = (float)(src.rows - j) ;
    }
  }

  remap( src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0) );

  return dst;
}

void FacesRecognition::SaveFace(cv::Rect face, uint16_t n ) {
  // Save face
  std::string file_name = "face_#" + std::to_string(n) + ".jpg";
  cv::Mat corp(src_image, face); // Copy?
  cv::Mat reflected_face = Reflect(corp);
  cv::imwrite(people_.ExtractPath() + file_name, reflected_face);
}

People FacesRecognition::CollectPeople( ) {
  using namespace cv;
  //-- 3. Apply the classifier to the image
  std::vector<Rect> faces;
  Mat frame_gray;

  cvtColor( src_image, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  auto i = 0;
  for( auto face:faces) {
    Head man;
    man.face_ = face;

    Mat faceROI = frame_gray( face );

    //-- In each face, detect eyes
    eyes_cascade.detectMultiScale( faceROI, man.eyes_, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    //-- In each face, detect mouth
    mouth_cascade.detectMultiScale( faceROI, man.mouths_, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    people_.add_man(man);
    SaveFace(face, i++);
  }

  //-- Show what you got
  //imshow( "Foo", image );
  // int c = waitKey(10);
  return people_.people();
}
