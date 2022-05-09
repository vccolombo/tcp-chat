cmake_minimum_required(VERSION 3.21)
project(server)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(server src/main.cpp src/server.h src/connection.cpp src/connection.h src/connectionchat.cpp src/connectionchat.h src/connectionfactory.h src/connectionfactory.cpp src/server.cpp src/connectionchatfactory.cpp src/connectionchatfactory.h)
