cmake_minimum_required(VERSION 3.9)

add_executable(client client_main.cpp)
add_executable(server server_main.cpp server.cpp entities.cpp manager.cpp)

target_link_libraries(server ${DEPEND_LIBS})
target_link_libraries(client ${DEPEND_LIBS})

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(server ${SFML_LIBRARIES})
    target_link_libraries(client ${SFML_LIBRARIES})
endif()
