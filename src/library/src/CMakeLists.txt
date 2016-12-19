
set(HEADERS
    ${OPENCV_BUILD_DIR}/include/
    ${CMAKE_SOURCE_DIR}/src/library/include/
)

file( GLOB SRC *.cc *.h)
set(LIB_FACE_FINDER Engine)

add_library(${LIB_FACE_FINDER}  SHARED ${SRC})
set_target_properties(${LIB_FACE_FINDER} PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

target_include_directories(${LIB_FACE_FINDER} PUBLIC ${HEADERS})

if (UNIX)
    SET (THREAD_LIB -Wl,--whole-archive -lpthread -Wl,--no-whole-)
    target_link_libraries (${LIB_FACE_FINDER} ${THREAD_LIB})
endif (UNIX)
