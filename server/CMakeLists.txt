cmake_minimum_required(VERSION 3.21)
project(server)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

file(GLOB SRC
     "src/*.h"
     "src/*.cpp"
)

add_executable(server ${SRC})
