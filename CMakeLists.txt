cmake_minimum_required(VERSION 3.20)
project(canal)

set(CMAKE_CXX_STANDARD 17)

include_directories(framework)
add_executable(canal main.cpp)

add_subdirectory(example/chat_room/chat_server)
add_subdirectory(example/chat_room/chat_client)
