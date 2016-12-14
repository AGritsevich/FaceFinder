#include "FaceFinderLib.h"
#include "FacesRecognition.h"
#include "threadpool.h"
#include "Utils.h"
#include "defines.h"

void Find_faces_in_folder( const char* root_folder, const uint32_t nThreads) {
  FacesRecognition recognator;

  if (!recognator.Init()) {
    return;
  }

  ThreadPool pool(nThreads);
  ImagesPathes img_pathes = FilesystemHelper::GetAllImagesInFolder(root_folder);
  // Start proceed
  // It's looks little strange, but I have no time do it better
  // TODO refactoring
  std::deque<AsyncDataPair> all_data;
  AsyncDataList on_level_data; // one folder
  std::string working_dir = FilesystemHelper::ExtractPath(img_pathes[0]);
 
  for(auto& path:img_pathes ) {
    const std::string new_dir = FilesystemHelper::ExtractPath(path);
    if (0 != working_dir.compare(new_dir)) {
       all_data.push_back({on_level_data, working_dir});
       on_level_data.clear();
       working_dir = new_dir;
     }
     AsyncData async_keeper = pool.runAsync<People>(&FacesRecognition::ThreadFacade, &recognator, path);
     on_level_data.push_back(async_keeper);
  }
  // save last
  all_data.push_back({on_level_data, working_dir});
  on_level_data.clear();
 
   // Wait
   pool.waitFinishAllTasks();
 
   // Collect proceed data
   while(!all_data.empty()) { // proceed by folder
     JsonAdapter::SaveJson(all_data.back());
     all_data.pop_back();
   }
}


