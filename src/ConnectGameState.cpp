#include "ConnectGameState.h"
#include "Graphics/Button.h"
#include "Graphics/TextBox.h"
#include "Graphics/Label.h"
#include "Game.h"
#include "Constants.h"

ConnectGameState::ConnectGameState(StateManager &stack, States::Context context) : State(stack, context) {
    mapSprite.setTileNumber(16);
    texture.loadFromFile("Resources/map1.png");
    texture.setSmooth(true);
    sf::IntRect rect{ TILE_SIZE * (16 % 15), TILE_SIZE * (16 / 15), TILE_SIZE, TILE_SIZE };
    mapSprite.setTexture(texture, rect);

    context.multiplayer->connect();

    if (!context.multiplayer->isConnected()) {
        std::cout << "[warning] no server connection" << std::endl;
    }

    auto textbox_new = std::make_shared<gui::Textbox>(getContext().fontHolder->get(Fonts::font1));
    auto textbox_join = std::make_shared<gui::Textbox>(getContext().fontHolder->get(Fonts::font1));

    textNew.setFont(context.fontHolder->get(Fonts::font1));
    textJoin.setFont(context.fontHolder->get(Fonts::font1));
    textNew.setString("New game:");
    textJoin.setString("Joind game:");
    textNew.setPosition(350, 150);
    textJoin.setPosition(350, 250);

    container.addWidget(textbox_new);
    container.addWidget(textbox_join);

    textbox_new->setDimensons(350, 200, 500, 50);
    textbox_new->setInd(0);
    textbox_new->setString("Game name");
    textbox_join->setDimensons(350, 300, 500, 50);
    textbox_join->setInd(0);
    textbox_join->setString("Game id");

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
    container.updateWidgets(dt);
    for (auto &&event: getContext().multiplayer->incoming) {
        switch (event.type) {
            case 'n': {
                std::cout << "[success] game id " << event.value << std::endl;
                gameID = event.value;
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
    getContext().window->clear(sf::Color(0, 165, 80, 0));
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            mapSprite.setPosition(static_cast<float >(j * TILE_SIZE), static_cast<float>(i * TILE_SIZE));
            getContext().window->draw(mapSprite);
        }

    getContext().window->draw(container);
}