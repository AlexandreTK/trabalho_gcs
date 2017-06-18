set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

#set(CMAKE_CXX_COMPILER "clang++")
#set(CMAKE_CXX_FLAGS "-Wall -W -Wno-unused-private-field -Wno-unused-parameter -Wno-reorder -Wno-delete-non-virtual-dtor -ansi -pedantic -g -Iinclude/ -O2")

file( GLOB SRCS *.c *.cpp *.h)
add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
