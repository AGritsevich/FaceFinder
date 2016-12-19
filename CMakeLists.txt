cmake_minimum_required (VERSION 2.8.11)
project (FaceFinder)

set(OPENCV_SUBMODULE_DIR ${CMAKE_SOURCE_DIR}/opencv/ )
get_filename_component(OPENCV_BUILD_DIR ${CMAKE_SOURCE_DIR}/opencv_build_dir/ REALPATH)

if((NOT OPENCV_SUBMODULE_DIR) OR (NOT EXISTS ${OPENCV_SUBMODULE_DIR}/include/))
    message(STATUS "Unable to find OpenCV submodule dir")

    # manualy run git submodule init
    execute_process(COMMAND git submodule update --init)
else()
    message(STATUS "OpenCV submodule found")
endif()

IF(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif(CMAKE_BUILD_TYPE STREQUAL "")
message(STATUS "BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

if((NOT EXISTS ${OPENCV_BUILD_DIR}))
    message(STATUS "Build opencv")
    make_directory(${CMAKE_BINARY_DIR}/opencv/)
    execute_process(
        COMMAND cmake ${OPENCV_SUBMODULE_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${OPENCV_BUILD_DIR}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/opencv/
    )
    execute_process(COMMAND make -j6 WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/opencv/ )
    execute_process(COMMAND make install WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/opencv/ )
    file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/opencv/)
endif()

# Pre-learning db
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/bin/haarcascade_frontalface_alt.xml )
    message(STATUS "Copy haarcascade_frontalface_alt.xml")
    configure_file(${OPENCV_BUILD_DIR}/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml ${CMAKE_SOURCE_DIR}/bin/ COPYONLY)
endif(NOT EXISTS ${CMAKE_SOURCE_DIR}/bin/haarcascade_frontalface_alt.xml )

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/bin/haarcascade_eye_tree_eyeglasses.xml )
    message(STATUS "Copy haarcascade_eye_tree_eyeglasses.xml")
    configure_file(${OPENCV_BUILD_DIR}/share/OpenCV/haarcascades/haarcascade_eye_tree_eyeglasses.xml ${CMAKE_SOURCE_DIR}/bin/ COPYONLY)
endif(NOT EXISTS ${CMAKE_SOURCE_DIR}/bin/haarcascade_eye_tree_eyeglasses.xml )

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/bin/haarcascade_smile.xml )
    message(STATUS "Copy haarcascade_smile.xml")
    configure_file(${OPENCV_BUILD_DIR}/share/OpenCV/haarcascades/haarcascade_smile.xml ${CMAKE_SOURCE_DIR}/bin/ COPYONLY)
endif(NOT EXISTS ${CMAKE_SOURCE_DIR}/bin/haarcascade_smile.xml )

# Prepare and configure build of FaceFinder
add_compile_options(-std=c++11) # CMake 2.8.12 or newer

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory (src/app/)
add_subdirectory (src/library/src/)
