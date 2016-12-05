#include <iostream>
#include <string>
#include <stdint.h>
#include "src/library/FaceFinderLib.h"

#ifdef __linux__ 
#include <dlfcn.h>
#else // WIN32

#endif
#include <windows.h>

class DynamicLibraryConnector {
public:
  typedef void (__cdecl *IMGPROCDLL)(std::string, uint32_t);
  virtual bool Open(std::string lib_path) =0;
  virtual bool Close() =0;
  virtual IMGPROCDLL LibraryFunction(std::string name) =0;
};

#ifdef __linux__ 
class DynamicLibraryConnectorLinux : public DynamicLibraryConnector {
  DynamicLibraryConnectorLinux() :
    hinstLib_(nullptr) {};
  virtual ~DynamicLibraryConnectorLinux(){Close();};

  IMGPROCDLL LibraryFunction(std::string name) override {
    IMGPROCDLL funptr; 
    if (hinstLib_ != NULL) { 
      funptr = dlsym(hinstLib_, name.c_str());
      char error* = nullptr;
      if ((error = dlerror()) != NULL) {
        std::cout << "--Error! " << dlerror() << std::endl;
        return nullptr;
      } 
      return ProcAdd;
    } 
    return nullptr;
  }

  bool Open(std::string lib_path) override {
    hinstLib_ = dlopen(lib_path.c_str(), RTLD_LAZY);

    if (!hinstLib_) {
      std::cout << "--Error! " << dlerror() << std::endl;
      return false;
    }
    return true;
  }

  bool Close() {
    bool retVal = (0 == dlclose(hinstLib_);
    hinstLib_ = nullptr;
    return retVal; 
  }

private:
  void *hinstLib_;
};
#else // WIN32
class DynamicLibraryConnectorWindows : public DynamicLibraryConnector {
public:
  DynamicLibraryConnectorWindows():
    hinstLib_(nullptr) {};
  virtual ~DynamicLibraryConnectorWindows(){Close();};

  IMGPROCDLL LibraryFunction(std::string name) override {
    IMGPROCDLL ProcAdd; 
    if (hinstLib_ != NULL) { 
      ProcAdd = (IMGPROCDLL) GetProcAddress(hinstLib_, name.c_str()); 

      if (NULL != ProcAdd) {
        //(ProcAdd) (L"Message sent to the DLL function\n"); 
        return ProcAdd;
      }
    } 
    return nullptr;
  }

  bool Open(std::string lib_path) override {
    hinstLib_ = LoadLibrary(TEXT(lib_path.c_str())); 
    return hinstLib_ != NULL;
  }

  bool Close() {
    bool retVal = (TRUE == FreeLibrary(hinstLib_));
    hinstLib_ = nullptr;
    return retVal; 
  }

private:
  HINSTANCE hinstLib_;
};
#endif // WIN32

int main(int argc, char** argv) {
  int retVal = 1;
  const std::string kHelpMessage = "Face detections program.\n  \
                                findface help - show this help message\n \
                                findface [folder_with_images] [count_of_threads]\n \
                                  folder_with_images - obligatory parameter\n \
                                  count_of_threads - optional, by default is 1";

  std::string first_param; // mandatory
  uint32_t second_param = 1; //optional - default

  switch(argc) {
  case 0:
  case 1:
  default:
    std::cout << kHelpMessage << std::endl;
    return retVal;
  case 3:
    second_param = std::atoi(argv[2]);
  case 2:
    first_param = argv[1];
    break;
  }

  if(0 == first_param.compare("help")) {
    std::cout << kHelpMessage << std::endl;
    return retVal;
  }

  DynamicLibraryConnector* connector = nullptr;
#ifdef __linux__ 
  connector = new DynamicLibraryConnectorLinux();
#else // WIN32
  connector = new DynamicLibraryConnectorWindows();
#endif

  if (connector->Open(kLibName)) {
    DynamicLibraryConnector::IMGPROCDLL processor = connector->LibraryFunction(kFunName);
    if (processor) {
      (processor)(first_param, second_param);
      retVal = 0;
    } else {
      std::cout << "--Error! Cannot find function in library! Function " << kFunName;
      retVal = 1;
    }
  } else {
    std::cout << "--Error! Cannot open library! Library " << kLibName;
    retVal = 1;
  }

  delete connector;

  return retVal;
}