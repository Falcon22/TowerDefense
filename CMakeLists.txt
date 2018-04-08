cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

project(server)
project(client)

add_subdirectory(src)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)
find_package(SFML REQUIRED system window graphics network)
include_directories(${INCLUDE_DIRS})