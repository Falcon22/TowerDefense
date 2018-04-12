#ifndef TOWERDEFENSE_GAMESTATE_H
#define TOWERDEFENSE_GAMESTATE_H

#include <SFML/System/Time.hpp>

#include "ResourceManager/ResourcesHolder.h"
#include "ResourceManager/ResourcesIdentifier.h"

#include "State.h"
#include "Graphics/Gui.h"

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

};


#endif //TOWERDEFENSE_GAMESTATE_H
