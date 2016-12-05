#include "FaceFinderLib.h"
#include "FacesKeeper.h"
#include "FacesRecognition.h"
#include "threadpool.h"
#include "JsonAdapter.h"
#include "defines.h"

typedef std::shared_ptr<AData<People>> AsyncData;
typedef std::deque<AsyncData> AsyncDataList;
typedef std::pair<AsyncDataList, std::string> AsyncDataPair;

ImagesPathes GetAllImagesInFolder(std::string path) {
  ImagesPathes imgs;
  cv::glob(path, imgs, true); // true - recursive
  // return sorted strings
  return imgs;
}

bool comparator(const Head& lhs, const Head& rhs)
{
  return true;
}

void Find_faces_in_folder( const char* root_folder, uint16_t nThreads)
{
  ThreadPool pool(nThreads);

  ImagesPathes img_pathes = GetAllImagesInFolder(root_folder);
  FacesRecognition recognator;
  // Start proceed
  // It's looks little strange, but I have no time do it better
  // TODO optimize
  std::deque<AsyncDataPair> all_data;
  AsyncDataList on_level_data;
  std::string working_dir = img_pathes[0];
 
  for(auto path:img_pathes ) {
    std::string new_dir = FacesKeeper::ExtractPath(path);
    if (0 != working_dir.compare(new_dir)) {
       all_data.push_back(std::make_pair(on_level_data, working_dir));
       on_level_data.clear();
       working_dir = new_dir;
     }
      AsyncData async_keeper = pool.runAsync<People>(&FacesRecognition::ThreadFacade, &recognator, path);
      on_level_data.push_back(async_keeper);
  }
 
   // Wait
   pool.waitFinishAllTasks();
 
   // Collect proceed data
   while(!all_data.empty()) {
     auto dir_img = std::get<0>(all_data.back());
     std::string dir = std::get<1>(all_data.back());
     People people;
 
     while(!dir_img.empty()) {
       AsyncData proceed_img = dir_img.back();
       People new_part = proceed_img->data;
       People result_merge;
       std::merge (people.begin (), people.end (), new_part.begin (), new_part.end (), result_merge.begin (), comparator);
       dir_img.pop_back();
       people.clear();
       people = result_merge;
     }
     JsonAdapter::SaveJson(people, dir);
     people.clear();
     all_data.pop_back();
   }
}


