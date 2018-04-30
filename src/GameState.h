#ifndef TOWERDEFENSE_GAMESTATE_H
#define TOWERDEFENSE_GAMESTATE_H

#include <SFML/System/Time.hpp>

#include "ResourceManager/ResourcesHolder.h"
#include "ResourceManager/ResourcesIdentifier.h"

#include "State.h"
#include "Graphics/Gui.h"
#include "Map.h"
#include "Units/Warrior/Warrior.h"
#include "Units/UnitsGraphics/GraphicsUnit.h"

class Tower;
class Bullet;

class GameState : public State {
public:
    explicit GameState(StateManager& stack, States::Context context);
    ~GameState() = default;

    bool handleEvent(const sf::Event &event) override;
    bool update(sf::Time dt) override;
    void draw() override;

private:
    Player::GameData gameData;
    gui::Gui containter;


    Map map;
    std::vector<sf::IntRect> roadRect;
    std::vector<Warrior *> warriors;
    std::vector<GraphicsUnit *> gUnits;
    Tower* tower;
    std::vector<Bullet*> bullets;
    sf::Sprite towerSprite;
    sf::Sprite bulletSprite;
};


#endif //TOWERDEFENSE_GAMESTATE_H
