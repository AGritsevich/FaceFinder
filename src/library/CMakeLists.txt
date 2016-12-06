
set(HEADERS)
set(SOURCES)
include_directories($ENV{OPENCV_INCLUDE_DIR})
file( GLOB SRC *.cc *.h)

add_library(FindFaces SHARED ${SRC})

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    MESSAGE(STATUS "64 bits compiler detected" )
	set(LIB_DIRECTORY $ENV{OPENCV_LIB_DIRx64})
else() 
    MESSAGE(STATUS "32 bits compiler detected" )
	set(LIB_DIRECTORY $ENV{OPENCV_LIB_DIRx86})
endif()

message(STATUS "LIB_DIRECTORY: " ${LIB_DIRECTORY})

set(CORE_LIB opencv_core2413.lib)
set(IMGPROC_LIB opencv_imgproc2413.lib)
set(HIGHGUI_LIB opencv_highgui2413.lib)
set(OBJECTDETECT_LIB opencv_objdetect2413.lib)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS debug mode)
	set(CORE_LIB opencv_core2413d)
	set(IMGPROC_LIB opencv_imgproc2413d)
	set(HIGHGUI_LIB opencv_highgui2413d)
	set(OBJECTDETECT_LIB opencv_objdetect2413d)
ENDIF()

find_library(OPENCV_CORE_LIB ${CORE_LIB} HINTS ${LIB_DIRECTORY})
message(STATUS "OPENCV_CORE_LIB: " ${OPENCV_CORE_LIB})
find_library(OPENCV_IMGPROC_LIB ${IMGPROC_LIB} HINTS ${LIB_DIRECTORY})
message(STATUS "OPENCV_IMGPROC_LIB: " ${OPENCV_IMGPROC_LIB})
find_library(OPENCV_HIGHGUI_LIB ${HIGHGUI_LIB} HINTS ${LIB_DIRECTORY})
message(STATUS "OPENCV_HIGHGUI_LIB: " ${OPENCV_HIGHGUI_LIB})
find_library(OPENCV_OBJDETECT_LIB ${OBJECTDETECT_LIB} HINTS ${LIB_DIRECTORY})
message(STATUS "OPENCV_OBJDETECT_LIB: " ${OPENCV_OBJDETECT_LIB})

target_link_libraries( FindFaces ${OPENCV_CORE_LIB} ${OPENCV_IMGPROC_LIB} ${OPENCV_HIGHGUI_LIB} ${OPENCV_OBJDETECT_LIB})
#target_link_libraries( DisplayImage $ENV{$ENV{LIB_DIRECTORY})