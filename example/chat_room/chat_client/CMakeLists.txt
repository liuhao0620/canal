cmake_minimum_required(VERSION 3.20)

project(chat_client)

set(CMAKE_CXX_STANDARD 17)

#set(BOOST_ROOT /usr/local/Cellar/boost/1.76.0)

#find_package(Boost COMPONENTS regex system REQUIRED)
find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS} ../../../framework . ../protocol processer)
add_executable(chat_client main.cpp ../protocol/chat_room.pb.cc)
target_link_libraries(chat_client ${Protobuf_LIBRARIES})

