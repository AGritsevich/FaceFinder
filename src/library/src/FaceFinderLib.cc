#include "FaceFinderLib.h"
#include "FacesRecognition.h"
#include "threadpool.h"
#include "Utils.h"
#include "defines.h"
#include <opencv2/core/core.hpp>

void Find_faces_in_folder( const char* root_folder, const uint32_t nThreads) {
  try {
      FacesRecognition recognator;

      ThreadPool pool(nThreads);
      std::vector<cv::String> img_pathes;
      std::cout << "Init complete" << std::endl;

      FilesystemHelper::GetAllImagesInFolder(root_folder, img_pathes);
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
   } catch(const char* error) {
        std::cout << "--Error! " << error << ". Programm will be terminated." << std::endl;
    }
    catch(...) {
        std::cout << "--Error! " << "Undefined error" << ". Programm will be terminated." << std::endl;
    }
}


