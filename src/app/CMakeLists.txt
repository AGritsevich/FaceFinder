include_directories(${CMAKE_SOURCE_DIR})
file( GLOB SRC *.cc *.h)
add_executable(FindFaceApp ${SRC})

if (UNIX)
    target_link_libraries (FindFaceApp -ldl)
endif (UNIX)
