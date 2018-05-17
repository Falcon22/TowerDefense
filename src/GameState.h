#ifndef TOWERDEFENSE_GAMESTATE_H
#define TOWERDEFENSE_GAMESTATE_H

#include <SFML/System/Time.hpp>
#include <utility>
#include "ResourceManager/ResourcesHolder.h"
#include "ResourceManager/ResourcesIdentifier.h"
#include "State.h"
#include "Graphics/Gui.h"
#include "Map.h"
#include "Units/Warrior/Warrior.h"
#include "Graphics/Button.h"
#include "Graphics/HUD.h"
#include "Graphics/GraphicsUnits/GraphicsUnitManager.h"
#include "Units/LogicUnitsManager.h"
#include "GameConstants.h"


class GameState : public State {
public:
    explicit GameState(StateManager& stack, States::Context context);

    bool handleEvent(const sf::Event &event) override;
    bool update(sf::Time dt) override;
    void draw() override;

    void manageEvents();

    GameConstants& gameConst = GameConstants::instance();

private:
    void initTower();
    void initHUD();

//    struct Event {
//        Event(int id_, char type_, std::string value_, const sf::Time time_) :
//                id(id_),
//                type(type_),
//                value(std::move(value_)),
//                time(time_) {}
//        int id;
//        char type;
//        std::string value;
//        sf::Time time;
//    };

    std::vector<mp::Event> events;
    sf::Time clock;

    float waveTimer;

    Player::GameData gameData;
    gui::Gui containter;
    gui::HUD hud;
    Map map;

    LogicUnitsManager lComponent;
    GraphicsUnitManager gComponent;

    std::vector<sf::Vector2f> towers1;
    std::vector<sf::Vector2f> towers2;
    gui::Gui container;
    gui::Gui buttons;
    std::vector<Map::LogicMap> roadRect;

    std::shared_ptr<Castle> curPlayer;
};


#endif //TOWERDEFENSE_GAMESTATE_H