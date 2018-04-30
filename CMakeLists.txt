cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)

project(server)
project(TowerDefense)

#add_subdirectory(src)

add_executable(server src/server_main.cpp src/Server/Server.cpp src/Server/Entities.cpp src/Server/Manager.cpp)
add_executable(TowerDefense  src/main.cpp src/Game.cpp src/Game.h src/ResourceManager/ResourcesHolder.h
        src/ResourceManager/ResourcesIdentifier.h src/Graphics/Button.cpp src/Graphics/Button.h src/GameContext.h
        src/GameState.cpp src/GameState.h src/GameStates.h src/Graphics/Gui.cpp src/Graphics/Gui.h src/Graphics/HUD.cpp src/Graphics/HUD.h
        src/Graphics/Icon.h src/Graphics/Icon.cpp src/Graphics/Label.cpp src/Graphics/Label.h src/MenuState.cpp src/MenuState.h
        src/PauseState.cpp src/PauseState.h src/State.cpp src/State.h src/StateManager.cpp
        src/StateManager.h src/Graphics/Widget.h src/Map.h src/Map.cpp src/Constants.h src/Tile.h src/Tile.cpp
        src/Units/Warrior/Warrior.cpp src/Units/Warrior/Warrior.h src/Units/Warrior/WarriorLvlOne.cpp
        src/Units/Warrior/WarriorLvlOne.h src/Units/UnitsGraphics/GraphicsUnit.cpp src/Units/UnitsGraphics/GraphicsUnit.h
        src/Units/Warrior/WarriorLvlTwo.cpp src/Units/Warrior/WarriorLvlTwo.h src/Units/Tower/Tower.cpp src/Units/Tower/Tower.h
        src/Units/GameUnit.cpp src/Units/GameUnit.h src/Units/Tower/TowerLvlZero.cpp src/Units/Tower/TowerLvlZero.h
        src/Units/Tower/TowerLvlOne.cpp src/Units/Tower/TowerLvlOne.h src/Units/Tower/TowerLvlTwo.cpp src/Units/Tower/TowerLvlTwo.h
        src/Units/Bullet/Bullet.cpp src/Units/Bullet/Bullet.h src/Units/Bullet/BulletLvlOne.cpp src/Units/Bullet/BulletLvlOne.h
        src/Units/Bullet/BulletLvlTwo.h src/Units/Bullet/BulletLvlTwo.cpp src/Units/Tower/TowerLvlThree.cpp src/Units/Tower/TowerLvlThree.h src/Server/Client.cpp src/Server/Client.h)

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
FIND_PACKAGE(SFML 2 REQUIRED system window graphics network audio)

#INCLUDE(FindPkgConfig)
#PKG_SEARCH_MODULE(SFML REQUIRED sfml)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(server ${SFML_LIBRARIES})
TARGET_LINK_LIBRARIES(TowerDefense ${SFML_LIBRARIES})
file(COPY Resources DESTINATION .)
