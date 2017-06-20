cmake_minimum_required(VERSION 2.8)
project(katw)

set (PROJECT_SRC_DIR     "${PROJECT_SOURCE_DIR}/src")

include(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${PROJECT_DATA_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

file(GLOB_RECURSE SOURCES "${PROJECT_SRC_DIR}/*.cpp" "${PROJECT_SRC_DIR}/*.c" "${PROJECT_SRC_DIR}/*.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
 

INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}  DESTINATION /bin)

add_custom_command(TARGET katw POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/data /var/lib/katw/data)

#add_custom_command(TARGET katw POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy
#                   ${CMAKE_CURRENT_BINARY_DIR}/katw /bin)
