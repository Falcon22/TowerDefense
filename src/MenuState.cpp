#include "MenuState.h"
#include "Graphics/Button.h"
#include "Game.h"

MenuState::MenuState(StateManager &stack, States::Context context): State(stack, context) {
    initButtons();
}

bool MenuState::handleEvent(const sf::Event &event) {
    container.handleWidgetsEvent(event);
    return false;
}

void MenuState::initButtons() {
    sf::Texture buttonTexture = getContext().textureHolder->get(Textures::button);
    sf::RenderWindow& window = *getContext().window;
    auto singlePlayer = std::make_shared<gui::Button>();

    singlePlayer->setTexture(buttonTexture);
    singlePlayer->setTexture(getContext().textureHolder->get(Textures::button));
    singlePlayer->setPosition({static_cast<float>(window.getSize().x / 3 - 40),
                       static_cast<float>(window.getSize().y / 2 - 40 * 3)});
    singlePlayer->setScale(2.0f, 2.0f);
    singlePlayer->setFont(getContext().fontHolder->get(Fonts::font1));
    singlePlayer->setText("Singleplayer");
    singlePlayer->setInd(0);
    singlePlayer->setCallback([this](int ind) {
        popState();
        pushState(States::ID::Game);
    });
    container.addWidget(singlePlayer);

    auto multiPlayer = std::make_shared<gui::Button>();

    multiPlayer->setTexture(buttonTexture);
    multiPlayer->setTexture(getContext().textureHolder->get(Textures::button));
    multiPlayer->setPosition({static_cast<float>(window.getSize().x / 3 - 40),
                       static_cast<float>(window.getSize().y / 2 + 40)});
    multiPlayer->setScale(2.0f, 2.0f);
    multiPlayer->setFont(getContext().fontHolder->get(Fonts::font1));
    multiPlayer->setText("Multiplayer");
    multiPlayer->setInd(0);
    multiPlayer->setCallback([this](int ind) {
        popState();
        pushState(States::ID::ConnectGame);
    });
    container.addWidget(multiPlayer);

}


bool MenuState::update(sf::Time dt) {

}

void MenuState::draw() {
    getContext().window->draw(container);
}