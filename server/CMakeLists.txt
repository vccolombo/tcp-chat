cmake_minimum_required(VERSION 3.21)
project(server)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(server
        src/main.cpp src/server.cpp src/server.h src/connection.cpp src/connection.h src/networkmessage.cpp src/networkmessage.h src/const.h src/channel.cpp src/channel.h src/participant.cpp src/participant.h)
