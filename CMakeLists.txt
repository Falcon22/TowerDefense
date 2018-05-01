cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)

project(server)
project(TowerDefense)

#add_subdirectory(src)

add_executable(server src/server_main.cpp src/Server/Server.cpp src/Server/Entities.cpp src/Server/Manager.cpp)
add_executable(TowerDefense  src/main.cpp src/Game.cpp src/Graphics/Button.cpp
        src/GameState.cpp src/Graphics/Gui.cpp src/Graphics/HUD.cpp
        src/Graphics/Icon.cpp src/Graphics/Label.cpp src/MenuState.cpp
        src/PauseState.cpp src/State.cpp src/StateManager.cpp
        src/Map.cpp src/Tile.cpp
        src/Units/Warrior/Warrior.cpp src/Units/Warrior/WarriorLvlOne.cpp
        src/Units/UnitsGraphics/GraphicsUnit.cpp
        src/Units/Warrior/WarriorLvlTwo.cpp src/Units/Tower/Tower.cpp
        src/Units/GameUnit.cpp src/Units/Tower/TowerLvlZero.cpp
        src/Units/Tower/TowerLvlOne.cpp src/Units/Tower/TowerLvlTwo.cpp
        src/Units/Bullet/Bullet.cpp src/Units/Bullet/BulletLvlOne.cpp
        src/Units/Bullet/BulletLvlTwo.cpp src/Units/Tower/TowerLvlThree.cpp src/Server/Client.cpp
        src/Server/Entities.cpp)

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
FIND_PACKAGE(SFML 2 REQUIRED system window graphics network audio)

#INCLUDE(FindPkgConfig)
#PKG_SEARCH_MODULE(SFML REQUIRED sfml)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(server ${SFML_LIBRARIES})
TARGET_LINK_LIBRARIES(TowerDefense ${SFML_LIBRARIES})
file(COPY Resources DESTINATION .)
