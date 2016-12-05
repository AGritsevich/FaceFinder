#include "FaceFinderLib.h"
#include "FacesKeeper.h"
#include "FacesRecognition.h"
#include <stdint.h>
#include "defines.h"
#include "threadpool.h"

ImagesPathes GetAllImagesInFolder(std::string path) {
  ImagesPathes imgs;
  cv::glob("/home/images/*.*", imgs, true); // true - recursive
  return imgs;
}

void Find_faces_in_folder( const char* root_folder, uint16_t nThreads)
{
  ThreadPool pool(nThreads);

  ImagesPathes img_pathes = GetAllImagesInFolder(root_folder);
  People data;
  FacesRecognition recognator;
  // Start proceed
   for(auto path:img_pathes ) {
     pool.runAsync(&recognator, path);
   }

  // Wait
  pool.waitFinishAllTasks();
}


