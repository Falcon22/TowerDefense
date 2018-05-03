#include "ConnectGameState.h"
#include "Graphics/Button.h"
#include "Game.h"

ConnectGameState::ConnectGameState(StateManager &stack, States::Context context) : State(stack, context) {
}

bool ConnectGameState::handleEvent(const sf::Event &event) {
    container.handleWidgetsEvent(event);
    return false;
}

bool ConnectGameState::update(sf::Time dt) {

}

void ConnectGameState::draw() {
    getContext().window->draw(container);
}