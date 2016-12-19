
set(HEADERS
    ${CMAKE_SOURCE_DIR}/
    ${CMAKE_SOURCE_DIR}/src/library/include/
)

set(APP_NAME FaceFinder)

file( GLOB SRC *.cc *.h)


add_executable(${APP_NAME} ${SRC})
set_target_properties(${APP_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
target_include_directories(${APP_NAME} PUBLIC ${HEADERS})

if (UNIX)
    target_link_libraries (${APP_NAME} -ldl)
endif (UNIX)

