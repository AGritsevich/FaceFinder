
set(HEADERS
    ${OPENCV_BUILD_DIR}/include/
    ${CMAKE_SOURCE_DIR}/src/include/
)

set(APP_NAME FaceFinder)

file( GLOB SRC *.cc *.h)


add_executable(${APP_NAME} ${SRC})
set_target_properties(${APP_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/
)
target_include_directories(${APP_NAME} PUBLIC ${HEADERS})


set(LIB_DIRECTORY ${OPENCV_BUILD_DIR}/lib/)
set(CORE_LIB ${OPENCV_BUILD_DIR}/lib/libopencv_core.so)
set(IMGPROC_LIB ${OPENCV_BUILD_DIR}/lib/libopencv_imgproc.so)
set(HIGHGUI_LIB ${OPENCV_BUILD_DIR}/lib/libopencv_highgui.so)
set(OBJECTDETECT_LIB ${OPENCV_BUILD_DIR}/lib/libopencv_objdetect.so)
set(IMGCODECS_LIB ${OPENCV_BUILD_DIR}/lib/libopencv_imgcodecs.so)

message(STATUS "lib CORE_LIB: " ${CORE_LIB})
message(STATUS "lib IMGPROC_LIB: " ${IMGPROC_LIB})
message(STATUS "lib HIGHGUI_LIB: " ${HIGHGUI_LIB})
message(STATUS "lib OBJECTDETECT_LIB: " ${OBJECTDETECT_LIB})

if (UNIX)
    SET (THREAD_LIB -Wl,--whole-archive -lpthread -Wl,--no-whole-)
    target_link_libraries (${APP_NAME} ${THREAD_LIB} ${CORE_LIB} ${IMGPROC_LIB} ${HIGHGUI_LIB} ${OBJECTDETECT_LIB} ${IMGCODECS_LIB})
endif (UNIX)
