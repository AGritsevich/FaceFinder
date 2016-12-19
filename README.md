# Face Finder

FaceFinder recursively search image files in root directory.
Than in multi threaded mode processing all image for faces.
Faces cutting from parent image and save near with parent file.
For one folder it creates result.json that contain X & Y coordinate in parent image for face, eyes, mouth.


Project uses: 
- OpenCV like submodule
- C++11

Clone  
git clone https://github.com/AGritsevich/FaceFinder

Build  

Windows 
Need update cmake files for Windows.

Linux  
Be ready, that in first cmake run it download OpenCV sources and build it.
In FaceFinder/
```bash
mkdir build/ && cd build
cmake .. && make
```
Run  

facefinder [root_folder] [count_of_thread]
