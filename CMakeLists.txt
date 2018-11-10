cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
project(playmusic)

include_directories(include /usr/include/SDL2/)

file(GLOB SOURCES "src/*.cc")

add_executable(
  playmusic
  ${SOURCES}  
)

target_link_libraries(playmusic stdc++fs SDL2 SDL2_mixer)
