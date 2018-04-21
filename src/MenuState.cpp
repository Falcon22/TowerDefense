#include "MenuState.h"
#include "Graphics/Button.h"
#include "Game.h"

MenuState::MenuState(StateManager &stack, States::Context context): State(stack, context) {
}

bool MenuState::handleEvent(const sf::Event &event) {
    container.handleWidgetsEvent(event);
    return false;
}

bool MenuState::update(sf::Time dt) {

}

void MenuState::draw() {

}