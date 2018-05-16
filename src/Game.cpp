#include "Game.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameState.h"
#include "ConnectGameState.h"
#include <thread>
#include "Server/Server.h"

Game::Game() : window({1216, 768}, "Tower Defense", sf::Style::Titlebar |
                                                     sf::Style::Default, sf::ContextSettings{0, 0, 8, 1, 1, 0}),
               client(constants::ip),
               context(window, font, textureHolder, fontHolder, cursor, 2, client.incoming, client.outcoming),
               stateManager(context) {
    loadAllResources();
    registerStates();
    stateManager.pushState(States::ID::Menu);
}

void Game::run() {
    const sf::Time frameTime = sf::seconds(1.f / 60.f);
    sf::Clock clock;
    sf::Time passedTime = sf::Time::Zero;

    if (client.isConnected()) {
        // TODO мультиплеерная мутота
        while (true) {
            char operation;
            std::cin >> operation;
            switch (operation) {
                case 'n': {
                    std::string game_name;
                    std::cin >> game_name;
                    client.outcoming.emplace_back(0, 'n', game_name, sf::microseconds(0)); //
                    break;
                }

                case 'j': {
                    std::string game_id;
                    std::cin >> game_id;
                    client.outcoming.emplace_back(0, 'j', game_id, sf::microseconds(0)); // Просим пустить в игру
                    break;
                }

                default: break;
            }

            client.sendEvents();

            if (operation == 'j')
                break;

            client.askEvents();
            if (!client.incoming.empty()) {
                std::cout << client.incoming[0].value << std::endl;
            }
            client.incoming.clear();
        }

        while (client.incoming.empty()) // тут мы запрашиваем айдишник
            client.askEvents();

        context.id = atoi(client.incoming[0].value.c_str());

        std::cout << "[client] player id is " << context.id << std::endl;
        client.incoming.clear();

    } else {
        std::cout << "[warning] no server connection" << std::endl;
    }

    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        passedTime += elapsedTime ;
        while (passedTime > frameTime) {
            passedTime -= frameTime;
            input();

            if (client.isConnected())
                try {
                    client.sendEvents();
                    client.askEvents();
                    for (auto &&item : client.incoming) {
                        if (item.type == 's' && item.value == "stop")
                            window.close();
                    }
                } catch (const std::exception &e) {
                    std::cout << e.what() << std::endl;
                }

            update(frameTime);
            client.incoming.clear();
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
    textureHolder.load(Textures::map, "Resources/map1.png");
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
    textureHolder.load(Textures::warriorOne, "Resources/enemyOne.png");
    textureHolder.load(Textures::warriorTwo, "Resources/enemy.png");
    textureHolder.load(Textures::blood, "Resources/blood.png");
    textureHolder.load(Textures::towerZero, "Resources/target.png");
    textureHolder.load(Textures::towerOneTop, "Resources/towerOneTop.png");
    textureHolder.load(Textures::towerOneBase, "Resources/towerOneBase.png");
    textureHolder.load(Textures::towerTwoTop, "Resources/towerTwoTop.png");
    textureHolder.load(Textures::towerTwoBase, "Resources/towerTwoBase.png");
    textureHolder.load(Textures::towerThreeTop, "Resources/towerThreeTop.png");
    textureHolder.load(Textures::towerThreeBase, "Resources/towerThreeBase.png");
    textureHolder.load(Textures::bulletOne, "Resources/bulletOne.png");
    textureHolder.load(Textures::bulletTwo, "Resources/bulletTwo.png");
    textureHolder.load(Textures::bulletThree, "Resources/bulletThree.png");
    textureHolder.load(Textures::explosionOne, "Resources/explosionOne.png");
    textureHolder.load(Textures::explosionTwo, "Resources/explosionTwo.png");
    textureHolder.load(Textures::explosionThree, "Resources/explosionThree.png");
    textureHolder.load(Textures::warriorIconOne, "Resources/warriorOne.png");
    textureHolder.load(Textures::warriorIconTwo, "Resources/warriorTwo.png");
    textureHolder.load(Textures::addWarriorOne, "Resources/addWarriorOne.png");
    textureHolder.load(Textures::addWarriorTwo, "Resources/addWarrior.png");
    textureHolder.load(Textures::addBarraks, "Resources/addBarraks.png");
    textureHolder.load(Textures::addFarm, "Resources/addFarm.png");
    textureHolder.load(Textures::addWeapons, "Resources/addWeapons.png");
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