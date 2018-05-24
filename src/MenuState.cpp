#include "MenuState.h"
#include "Graphics/Button.h"
#include "Game.h"
#include "Constants.h"

MenuState::MenuState(StateManager &stack, States::Context context): State(stack, context) {
    mapSprite.setTileNumber(16);
    texture.loadFromFile("Resources/map1.png");
    texture.setSmooth(true);
    sf::IntRect rect{ TILE_SIZE * (16 % 15), TILE_SIZE * (16 / 15), TILE_SIZE, TILE_SIZE };
    mapSprite.setTexture(texture, rect);

    name.setFont(context.fontHolder->get(Fonts::font1));
    name.setPosition({static_cast<float>(470),
                      static_cast<float>(150)});
    name.setScale(2.f, 2.f);
    name.setString("DATTACK");
    logo.setTexture(context.textureHolder->get(Textures::logo));
    logo.setPosition(270.f, -20.f);
    logo.setScale(1.f / 2, 1.f / 2);
    initButtons();
}

bool MenuState::handleEvent(const sf::Event &event) {
    container.handleWidgetsEvent(event);
    return false;
}

void MenuState::initButtons() {
    sf::Sprite buttonSprite;
    sf::Texture buttonTexture = getContext().textureHolder->get(Textures::button);
    sf::IntRect rect{ 0, 0, 618, 185};
    //buttonSprite.setTextureRect(rect);
    //buttonSprite.setTexture(buttonTexture);
    //buttonSprite.setPosition(100.f, 100.f);
    //getContext().window->draw(buttonSprite);
    sf::RenderWindow& window = *getContext().window;
    auto play = std::make_shared<gui::Button>();
    play->setTexture(getContext().textureHolder->get(Textures::button));
    play->setTextureRect(rect);
    play->setPosition({static_cast<float>(window.getSize().x / 3 - 100),
                       static_cast<float>(window.getSize().y / 2)});
    //play->setScale(1.0f, 1.0f);
    play->setFont(getContext().fontHolder->get(Fonts::font1));
    play->setText("Play");
    play->setInd(0);
    play->setCallback([this](int ind) {
        popState();
        pushState(States::ID::ConnectGame);
    });

    container.addWidget(play);
}


bool MenuState::update(sf::Time dt) {

}

void MenuState::draw() {
    getContext().window->clear(sf::Color(0, 165, 80, 0));
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            mapSprite.setPosition(static_cast<float >(j * TILE_SIZE), static_cast<float>(i * TILE_SIZE));
            getContext().window->draw(mapSprite);
        }

    //getContext().window->draw(name);
    getContext().window->draw(container);
    getContext().window->draw(logo);
}