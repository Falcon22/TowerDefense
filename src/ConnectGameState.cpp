#include "ConnectGameState.h"
#include "Graphics/Button.h"
#include "Graphics/TextBox.h"
#include "Game.h"

ConnectGameState::ConnectGameState(StateManager &stack, States::Context context) : State(stack, context) {
    auto textbox = std::make_shared<gui::Textbox>(getContext().fontHolder->get(Fonts::font1));
    container.addWidget(textbox);
    textbox->setDimensons(context.window->getSize().y / 3, context.window->getSize().x / 3, 500, 50);
    container.addWidget(textbox);
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