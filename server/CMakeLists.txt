cmake_minimum_required(VERSION 3.21)
project(server)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(server
        src/main.cpp src/server.cpp src/server.hpp src/connection.cpp src/connection.hpp src/networkmessage.cpp src/networkmessage.hpp src/const.hpp src/channel.cpp src/channel.hpp src/participant.cpp src/participant.hpp)
