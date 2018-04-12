#include "Game.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameState.h"

Game::Game() : window({1000, 1000}, "Tower Defense", sf::Style::Titlebar |
        sf::Style::Default, sf::ContextSettings{0, 0, 8, 1, 1, 0, false}),
               context(window, font, textureHolder, fontHolder, cursor),
               stateManager(context) {
    loadAllResources();
    registerStates();
    stateManager.pushState(States::ID::Game);
}

void Game::run() {
    const sf::Time frameTime = sf::seconds(1.f / 30.f);
    sf::Clock clock;
    sf::Time passedTIme = sf::Time::Zero;

    while (window.isOpen()) {
        input();
        update(frameTime);
        draw();
    }
}

void Game::input() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        stateManager.processEvents(event);
    }
}

void Game::loadAllResources() {
    fontHolder.load(Fonts::font1, "../Resources/sansation.ttf");
}


void Game::update(sf::Time frameTime) {
    stateManager.update(frameTime);
}

void Game::draw() {
    window.clear(sf::Color(210, 210, 210));
    stateManager.draw();
    window.display();
}

void Game::registerStates() {
    stateManager.registerState<GameState>(States::ID::Game);
}