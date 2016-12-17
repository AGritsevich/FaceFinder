#include <iostream>
#include <string>
#include <stdint.h>
#include <memory>
#include <algorithm>
#include "src/library/FaceFinderLib.h"

#ifdef __linux__ 
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#else // WIN32
#include <windows.h>
#endif

class DynamicLibraryConnector {
public:
  virtual bool Open(std::string lib_path) =0;
  virtual bool Close() =0;
  virtual IMGPROCDLL LibraryFunction(std::string name) =0;
  virtual ~DynamicLibraryConnector(){}
};

#ifdef __linux__ 
class DynamicLibraryConnectorLinux : public DynamicLibraryConnector {
public:
  DynamicLibraryConnectorLinux() :
    m_hinstLib(nullptr) {}
  virtual ~DynamicLibraryConnectorLinux(){Close();}

  bool Open(std::string lib_path) override {
    m_hinstLib = dlopen(lib_path.c_str(), RTLD_LAZY);

    if (!m_hinstLib) {
      std::cout << "--Error! " << dlerror() << std::endl;
      return false;
    }
    return true;
  }

  IMGPROCDLL LibraryFunction(std::string name) override {
    IMGPROCDLL funptr; 
    if (m_hinstLib != NULL) { 
      void* void_ptr = (dlsym(m_hinstLib, name.c_str()));
      funptr = reinterpret_cast<IMGPROCDLL>(reinterpret_cast<long>(void_ptr));
      char *error = nullptr;
      if ((error = dlerror()) != NULL) {
        std::cout << "--Error! " << dlerror() << std::endl;
        return nullptr;
      } 
      return funptr;
    } 
    return nullptr;
  }

  bool Close() {
    bool retVal = (0 == dlclose(m_hinstLib));
    m_hinstLib = nullptr;
    return retVal; 
  }

private:
  void *m_hinstLib;
};
#else // WIN32
class DynamicLibraryConnectorWindows : public DynamicLibraryConnector {
public:
  DynamicLibraryConnectorWindows():
    m_hinstLib(nullptr) {};
  virtual ~DynamicLibraryConnectorWindows(){Close();};

  IMGPROCDLL LibraryFunction(std::string name) override {
    IMGPROCDLL ProcAdd; 
    if (m_hinstLib != NULL) { 
      ProcAdd = (IMGPROCDLL) GetProcAddress(m_hinstLib, name.c_str()); 

      if (NULL != ProcAdd) {
        //(ProcAdd) (L"Message sent to the DLL function\n"); 
        return ProcAdd;
      }
    } 
    return nullptr;
  }

  bool Open(std::string lib_path) override {
    m_hinstLib = LoadLibrary(lib_path.c_str()); 

    if (m_hinstLib == NULL) {
      DWORD   dwLastError = ::GetLastError();
      TCHAR   lpBuffer[256] = {0};
      if(dwLastError != 0)    // Don't want to see a "operation done successfully" error ;-)
        ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,                 // It´s a system error
        NULL,                                      // No string to be formatted needed
        dwLastError,                               // Hey Windows: Please explain this error!
        MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),  // Do it in the standard language
        lpBuffer,              // Put the message here
        sizeof(lpBuffer)-1,                     // Number of bytes to store the message
        NULL);

        std::cout << "Error open library! Error code: " << dwLastError << ", " << lpBuffer << std::endl; 

        return false;
    }
    return true;
  }

  bool Close() {
    bool retVal = (TRUE == FreeLibrary(m_hinstLib));
    m_hinstLib = nullptr;
    return retVal; 
  }

private:
  HINSTANCE m_hinstLib;
};
#endif // WIN32

int main(int argc, char** argv) {
  int retVal = 1;
  const std::string kHelpMessage = "Face detections program.\n  \
                                findface help - show this help message\n \
                                findface [folder_with_images] [count_of_threads]\n \
                                  folder_with_images - obligatory parameter\n \
                                  count_of_threads - optional, by default is 1";

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

  std::unique_ptr<DynamicLibraryConnector> connector = nullptr;
#ifdef __linux__ 
  connector.reset(new DynamicLibraryConnectorLinux());
#else // WIN32
  connector.reset(new DynamicLibraryConnectorWindows());
#endif

  if (connector->Open(kLibName)) {
    IMGPROCDLL processor = connector->LibraryFunction(kFunName);
    if (processor) {
      (processor)(root_path.c_str(), count_of_threads);
      retVal = 0;
    } else {
      std::cout << "--Error! Cannot find function in library! Function " << kFunName;
      retVal = 1;
    }
  } else {
    std::cout << "--Error! Cannot open library! Library " << kLibName;
    retVal = 1;
  }

  return retVal;
}
