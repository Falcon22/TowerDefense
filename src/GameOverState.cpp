#include "GameOverState.h"
#include "Constants.h"

#include <fstream>
#include <cmath>

GameOverState::GameOverState(StateManager &stack, States::Context context)
        : State(stack, context)
{

    texture.loadFromFile("Resources/map1.png");
    texture.setSmooth(true);
    sf::IntRect rect{ TILE_SIZE * (16 % 15), TILE_SIZE * (16 / 15), TILE_SIZE, TILE_SIZE };
    mapSprite.setTexture(texture, rect);

    sf::RenderWindow &window = *context.window;
    sf::Font &font = *context.font;

//    sf::RenderWindow &window = *context.window;
//    sf::Font &font = *context.font;

    gameOvetText.setString("YOU LOSE");
    gameOvetText.setFillColor(sf::Color::White);
    gameOvetText.setCharacterSize(100);
    gameOvetText.setFont(context.fontHolder->get(Fonts::font1));
    gameOvetText.setPosition(350.f, 200.f);

    enterText.setString("ENTER Menu");
    enterText.setFillColor(sf::Color::Black);
    enterText.setCharacterSize(30);
    enterText.setFont(context.fontHolder->get(Fonts::font1));
    enterText.setPosition(500.f, 400.f);
}

bool GameOverState::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Return)
    {
        popState();
        pushState(States::ID::Menu);
    }

    return false;
}

bool GameOverState::update(sf::Time dt)
{
    return false;
}

void GameOverState::draw()
{
    getContext().window->clear(sf::Color(0, 165, 80, 0));
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            mapSprite.setPosition(static_cast<float >(j * TILE_SIZE), static_cast<float>(i * TILE_SIZE));
            getContext().window->draw(mapSprite);
        }

    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(gameOvetText);
    window.draw(enterText);
}