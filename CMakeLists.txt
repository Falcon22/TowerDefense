cmake_minimum_required(VERSION 3.6)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp src/Game.cpp src/Game.h src/ResourceManager/ResourcesHolder.h
        src/ResourceManager/ResourcesIdentifier.h src/Graphics/Button.cpp src/Graphics/Button.h src/GameContext.h
        src/GameState.cpp src/GameState.h src/GameStates.h src/Graphics/Gui.cpp src/Graphics/Gui.h src/Graphics/HUD.cpp src/Graphics/HUD.h
        src/Graphics/Icon.h src/Graphics/Icon.cpp src/Graphics/Label.cpp src/Graphics/Label.h src/MenuState.cpp src/MenuState.h
        src/PauseState.cpp src/PauseState.h src/State.cpp src/State.h src/StateManager.cpp
        src/StateManager.h src/Graphics/Widget.h src/Units/UnitsComponents/GameUnit.cpp src/Units/UnitsComponents/GameUnit.h
        src/Units/UnitsComponents/InputComponents/InputComponent.cpp src/Units/UnitsComponents/InputComponents/InputComponent.h
        src/Units/UnitsComponents/GraphicsComponents/GraphicsComponent.cpp src/Units/UnitsComponents/GraphicsComponents/GraphicsComponent.h
        src/Units/UnitsComponents/LogicComponents/LogicComponent.cpp src/Units/UnitsComponents/LogicComponents/LogicComponent.h
        src/Units/Tower.cpp src/Units/Tower.h src/Units/Warrior.cpp src/Units/Warrior.h src/Units/Bullet.cpp src/Units/Bullet.h
        src/Units/UnitsComponents/GraphicsComponents/TowerGraphicsComponent.cpp src/Units/UnitsComponents/GraphicsComponents/TowerGraphicsComponent.h
        src/Units/UnitsComponents/LogicComponents/WarriorLogicComponent.cpp src/Units/UnitsComponents/LogicComponents/WarriorLogicComponent.h
        src/Units/UnitsComponents/LogicComponents/TowerLogicComponent.cpp src/Units/UnitsComponents/LogicComponents/TowerLogicComponent.h
        src/Units/UnitsComponents/LogicComponents/BulletLogicComponent.cpp src/Units/UnitsComponents/LogicComponents/BulletLogicComponent.h
        src/Units/UnitsComponents/GraphicsComponents/BulletGraphicsComponent.cpp src/Units/UnitsComponents/GraphicsComponents/BulletGraphicsComponent.h
        src/Units/UnitsComponents/GraphicsComponents/WarriorGraphicsComponent.cpp
        src/Units/UnitsComponents/GraphicsComponents/WarriorGraphicsComponent.h src/Units/UnitsComponents/InputComponents/TowerInputComponent.cpp
        src/Units/UnitsComponents/InputComponents/TowerInputComponent.h src/Units/UnitsComponents/InputComponents/BulletInputComponent.cpp
        src/Units/UnitsComponents/InputComponents/BulletInputComponent.h src/Units/UnitsComponents/InputComponents/WarriorInputComponent.cpp
        src/Units/UnitsComponents/InputComponents/WarriorInputComponent.h)

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
FIND_PACKAGE(SFML 2 REQUIRED system window graphics network audio)

#INCLUDE(FindPkgConfig)
#PKG_SEARCH_MODULE(SFML REQUIRED sfml)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SFML_LIBRARIES})
file(COPY Resources DESTINATION .)