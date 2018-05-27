#pragma once

#include "State.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include "Tile.h"
class WinState : public State
{
public:
    explicit WinState(StateManager &stack, States::Context context);

    bool handleEvent(const sf::Event &event) override;
    bool update(sf::Time dt) override;
    void draw() override;

private:
    sf::Text winText, enterText;
    sf::Texture texture;
    Tile mapSprite;
};

