cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

project(server)
project(client)

#add_subdirectory(src)

add_executable(client src/client_main.cpp)
add_executable(server src/server_main.cpp src/server.cpp src/entities.cpp src/manager.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)
find_package(SFML REQUIRED system window graphics network)
include_directories(${INCLUDE_DIRS})

target_link_libraries(server ${DEPEND_LIBS})
target_link_libraries(client ${DEPEND_LIBS})

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(server ${SFML_LIBRARIES})
    target_link_libraries(client ${SFML_LIBRARIES})
endif()
