#pragma once

#include "State.h"
#include <iostream>
#include "Tile.h"

class GameOverState : public State
{
public:
    explicit GameOverState(StateManager &stack, States::Context context);

    bool handleEvent(const sf::Event &event) override;
    bool update(sf::Time dt) override;
    void draw() override;

private:
    sf::Text gameOvetText, enterText, scoreText;
    sf::Texture texture;
    Tile mapSprite;
};

