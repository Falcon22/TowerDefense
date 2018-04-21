#include "GameState.h"
#include "Game.h"

GameState::GameState(StateManager &stack, States::Context context) :
        State(stack, context),
        gameData(),
        map(*context.window)

{
    map.analyze();
}

bool GameState::handleEvent(const sf::Event &event) {

}

bool GameState::update(sf::Time dt) {

}

void GameState::draw() {
    map.draw();
}
