set(CMAKE_C_FLAGS "-Wall")
file( GLOB SRCS *.c *.cpp *.h)
add_executable(katw ${SRCS})
