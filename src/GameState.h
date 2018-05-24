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

    std::vector<mp::Event> events;
    sf::Time clock;

    float waveTimer;

    Player::GameData gameData;
    gui::Gui containter;

    Map map;

    LogicUnitsManager lComponent;
    GraphicsUnitManager gComponent;

    gui::HUD hud;
    std::vector<sf::Vector2f> towers1;
    std::vector<sf::Vector2f> towers2;
    gui::Gui container;
    gui::Gui buttons;
    std::vector<Map::LogicMap> roadRect;

    std::shared_ptr<Castle> curPlayer;
    int curPlayerRoad;
    sf::Sprite castle1;
    sf::Sprite castle2;
    sf::Text cost;
    bool printCost;
    sf::Text timer;
    sf::Text you;
    sf::Text foe;
};


#endif //TOWERDEFENSE_GAMESTATE_H