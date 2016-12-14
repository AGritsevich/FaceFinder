# Face Finder

This project contains library and app that dynamicly connect to application.
Application just validate input parameters and proxy connection to library for different OSes

Library recursively search image files image files in root directory.
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
For build it need install OpenCV and configure global path to OpenCV build directory "OPENCV_DIR".

Linux

Packages: 
[compiler] build-essential
[required] cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
[optional] install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev

Run  

findfacesapp [root_folder] [count_of_thread]
