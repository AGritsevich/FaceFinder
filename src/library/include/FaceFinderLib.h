#ifndef SRC_LIBRARY_INCLUDE_FACEFINDERLIB_H
#define SRC_LIBRARY_INCLUDE_FACEFINDERLIB_H

#include <stdint.h>
#include <string>

#ifdef __linux__ 
#define DLL_EXP
#define _C_
const char kLibName[] = "/home/anton/Work/FaceFinder/bin/libEngine.so";
#else // WIN32
#define DLL_EXP __declspec(dllexport)
#define _C_ __cdecl
#ifdef _DEBUG
#else
const char kLibName[] = "Engine.dll";
#endif // _DEBUG
#endif // WIN32

const char kFunName[] = "Find_faces_in_folder";

#ifdef __cplusplus    // If used by C++ code, 
 extern "C" {          // we need to export the C interface
#endif // __cpluspluso
  using  IMGPROCDLL = void (_C_ *)( const char*, const uint32_t);

  DLL_EXP void _C_ Find_faces_in_folder( const char*, const uint32_t nThreads );

#ifdef __cplusplus
 }
#endif // __cplusplus

#endif // SRC_LIBRARY_INCLUDE_FACEFINDERLIB_H

