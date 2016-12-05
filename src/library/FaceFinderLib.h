#ifndef SRC_LIBRARY_FACEFINDERLIB_H
#define SRC_LIBRARY_FACEFINDERLIB_H

#ifdef __linux__ 
#define DLL_EXP
#define _C_
const char kLibName[] = "FindFaces.so";
#else // WIN32
#define DLL_EXP __declspec(dllexport)
#define _C_ __cdecl
const char kLibName[] = "FindFaces.dll";
#endif // WIN32

const char kFunName[] = "Find_faces_in_folder";

#ifdef __cplusplus    // If used by C++ code, 
 extern "C" {          // we need to export the C interface
#endif // __cplusplus

 DLL_EXP void _C_ Find_faces_in_folder( const char* root_folder );

#ifdef __cplusplus
 }
#endif // __cplusplus

#endif // SRC_LIBRARY_FACEFINDERLIB_H

