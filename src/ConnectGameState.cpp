#include "ConnectGameState.h"
#include "Graphics/Button.h"
#include "Graphics/TextBox.h"
#include "Game.h"

ConnectGameState::ConnectGameState(StateManager &stack, States::Context context) : State(stack, context) {
    context.multiplayer->connect();

    if (!context.multiplayer->isConnected()) {
        std::cout << "[warning] no server connection" << std::endl;
    }

    auto textbox_new = std::make_shared<gui::Textbox>(getContext().fontHolder->get(Fonts::font1));
    auto textbox_join = std::make_shared<gui::Textbox>(getContext().fontHolder->get(Fonts::font1));

    container.addWidget(textbox_new);
    container.addWidget(textbox_join);

    textbox_new->setDimensons(50, 50, 500, 50);
    textbox_new->setInd(0);
    textbox_join->setDimensons(50, 200, 500, 50);
    textbox_join->setInd(0);

    textbox_new->setCallback([this, textbox_new](int ind) {
        getContext().multiplayer->outcoming.emplace_back(0, 'n', textbox_new->getString(), sf::microseconds(0));
    });

    textbox_join->setCallback([this, textbox_join](int ind) {
        getContext().multiplayer->outcoming.emplace_back(0, 'j', textbox_join->getString(), sf::microseconds(0));
    });
}

bool ConnectGameState::handleEvent(const sf::Event &event) {
    container.handleWidgetsEvent(event);
    return false;
}

bool ConnectGameState::update(sf::Time dt) {

    for (auto &&event: getContext().multiplayer->incoming) {
        switch (event.type) {
            case 'n': {
                std::cout << "[success] game id " << event.value << std::endl;
                break;
            }

            case 'j': {
                *getContext().p_id = atoi(event.value.c_str());
                std::cout << "[success] in game. your id " << *getContext().p_id << std::endl;
                popState();
                pushState(States::ID::Game);
                break;
            }

            default:
                break;
        }
    }

}

void ConnectGameState::draw() {
    getContext().window->draw(container);
}