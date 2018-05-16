#include "Game.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameState.h"
#include "ConnectGameState.h"
#include <thread>
#include "Server/Server.h"

Game::Game() : window({1000, 1000}, "Tower Defense", sf::Style::Titlebar |
        sf::Style::Default, sf::ContextSettings{0, 0, 8, 1, 1, 0}),
               context(window, font, textureHolder, fontHolder, cursor, new mp::ClientMultiplayerFacade),
               stateManager(context) {
    loadAllResources();
    registerStates();

    window.setVerticalSyncEnabled(true);
    stateManager.pushState(States::ID::Menu);
}


Game::Game(mp::player &first, mp::player &second)
        : context(window, font, textureHolder, fontHolder, cursor, new mp::ServerMultiplayerFacade(first, second)),
          stateManager(context)
{
    registerStates();
    stateManager.pushState(States::ID::Game); // TODO MultiplayerGame
}

void Game::run() {
    const sf::Time frameTime = sf::seconds(1.f / 60.f);
    sf::Clock clock;
    sf::Time passedTime = sf::Time::Zero;

    auto mp = context.multiplayer;
    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        passedTime += elapsedTime ;
        while (passedTime > frameTime) {
            passedTime -= frameTime;
            input();
            update(frameTime);

            mp->incoming.clear();
            if (mp->isConnected()) {
                try {
                    mp->sendEvents();
                    mp->askEvents();
                    for (auto &&item : mp->incoming) {
                        if (item.type == 's' && item.value == "stop")
                            window.close();
                    }
                } catch (const std::exception &e) {
                    std::cout << e.what() << std::endl;
                }
            } else {
                mp->outcoming.clear();
            }
        }

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
    fontHolder.load(Fonts::font1, "Resources/sansation.ttf");

    textureHolder.load(Textures::cursor, "Resources/cursor.png");
    textureHolder.load(Textures::panel, "Resources/panel.png");
    textureHolder.load(Textures::button, "Resources/button.png");
    textureHolder.load(Textures::map, "Resources/map.png");
    textureHolder.load(Textures::target, "Resources/target.png");
    textureHolder.load(Textures::gold, "Resources/diamond.png");
    textureHolder.load(Textures::star, "Resources/star.png");
    textureHolder.load(Textures::exit, "Resources/exit.png");
    textureHolder.load(Textures::lives, "Resources/heart.png");
    textureHolder.load(Textures::pauseOn, "Resources/pauseOn.png");
    textureHolder.load(Textures::pauseOff, "Resources/pauseOff.png");
    textureHolder.load(Textures::audioOff, "Resources/audioOff.png");
    textureHolder.load(Textures::audioOn, "Resources/audioOn.png");
    textureHolder.load(Textures::musicOff, "Resources/musicOff.png");
    textureHolder.load(Textures::musicOn, "Resources/musicOn.png");
    textureHolder.load(Textures::warriorLvlOne, "Resources/enemyOne.png");
    textureHolder.load(Textures::warriorLvlTwo, "Resources/enemy.png");
    textureHolder.load(Textures::towerOneTop, "Resources/towerOneTop.png");
    textureHolder.load(Textures::towerTwoTop, "Resources/towerTopTwo.png");
    textureHolder.load(Textures::towerOneBase, "Resources/towerOneBase.png");
    textureHolder.load(Textures::towerTwoBase, "Resources/towerBaseTwo.png");
    textureHolder.load(Textures::bulletOne, "Resources/bulletOne.png");
    textureHolder.load(Textures::bulletTwo, "Resources/bulletTwo.png");
    textureHolder.load(Textures::warriorLvlOne, "Resources/enemyOne.png");
}


void Game::update(sf::Time frameTime) {
    stateManager.update(frameTime);
}

void Game::draw() {
    window.clear(sf::Color(210, 210, 210));
//    std::thread t1(&StateManager::draw, stateManager);
//    t1.join();
    stateManager.draw();
    window.display();
}

void Game::registerStates() {
    stateManager.registerState<MenuState>(States::ID::Menu);
    stateManager.registerState<ConnectGameState>(States::ID::ConnectGame);
    stateManager.registerState<GameState>(States::ID::Game);
}

void Game::server_run(bool use_validation) {
    const sf::Time frameTime = sf::seconds(1.f / 60.f);
    sf::Clock clock;
    sf::Time passedTime = sf::Time::Zero;

    std::cout << "start multi game" << std::endl;
    
    auto& mp = context.multiplayer;
    while (true) {
        if (!mp->isConnected()) {
            mp->outcoming.emplace_back(0, 's', "stop", sf::microseconds(0));
            mp->sendEvents();

            break;
        }

        if (use_validation) {
            sf::Time elapsedTime = clock.restart();
            passedTime += elapsedTime ;
            while (passedTime > frameTime) {
                passedTime -= frameTime;
                update(frameTime);

                try {
                    mp->incoming.clear();
                    mp->sendEvents();
                    mp->askEvents();
                } catch (const std::exception &e) {
                    std::cout << e.what() << std::endl;
                }
            }
        } else {
            try {
                mp->incoming.clear();
                mp->askEvents();
                mp->outcoming = mp->incoming;
                mp->sendEvents();
            } catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
}
