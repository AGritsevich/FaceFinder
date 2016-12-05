include_directories(${CMAKE_SOURCE_DIR})
file( GLOB SRC *.cc *.h)
add_executable(FindFaceApp ${SRC})
#target_link_libraries (FindFaceApp LINK_PUBLIC Hello)