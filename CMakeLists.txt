cmake_minimum_required (VERSION 2.8.11)
project (TestTaskRegula)

set(OPENCV_SUBMODULE_DIR ${CMAKE_SOURCE_DIR}/opencv/ )
set(OPENCV_BUILD_DIR ${CMAKE_SOURCE_DIR}/opencv_build_dir/)

if((NOT OPENCV_SUBMODULE_DIR) OR (NOT EXISTS ${OPENCV_SUBMODULE_DIR}/include))
    message(STATUS "Unable to find OpenCV submodule dir")

    # manualy run git submodule init
    execute_process(COMMAND git submodule update --init)
else()
    message(STATUS "OpenCV submodule found")
endif()

# Prepare and configure build of OpenCV
get_filename_component(OPENCV_BUILD_DIR ${OPENCV_BUILD_DIR} REALPATH)
set(CMAKE_INSTALL_PREFIX ${OPENCV_BUILD_DIR}/)
add_subdirectory(${OPENCV_SUBMODULE_DIR})

# Prepare and configure build of FaceFinder
add_compile_options(-std=c++11) # CMake 2.8.12 or newer

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory (src)
