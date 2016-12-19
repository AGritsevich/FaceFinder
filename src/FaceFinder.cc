#include <iostream>
#include <string>
#include <stdint.h>
#include <algorithm>
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

int main(int argc, char** argv) {
  int retVal = 1;
  const std::string kHelpMessage = "Face detections program.\n"
                               " findface help - show this help message\n"
                               " findface [folder_with_images] [count_of_threads]\n"
                                 " folder_with_images - obligatory parameter\n"
                                 " count_of_threads - optional, by default is 1";

  std::string root_path; // mandatory
  uint32_t count_of_threads = 1u; //optional - default
  const uint64_t kMaxThreadCount = 256u;
  switch(argc) {
  case 0:
  case 1:
  default:
    std::cout << kHelpMessage << std::endl;
    return retVal;
  case 3:
    count_of_threads = std::min(std::stoul(argv[2]), kMaxThreadCount);
  case 2:
    root_path = argv[1];
    break;
  }

  if(0 == root_path.compare("help")) {
    std::cout << kHelpMessage << std::endl;
    return retVal;
  }

  Find_faces_in_folder(root_path.c_str(), count_of_threads);

  return retVal;
}
